#!/usr/bin/env python

import os
import sys
import pwd
import subprocess

PROJECT_PATH = os.path.dirname(os.path.realpath(__file__))
DOCKER_PATH = os.path.join(PROJECT_PATH, r'docker')

UID = os.getuid()
GID = os.getgid()
LOGIN = pwd.getpwuid(UID)[0]

class COMMON_CONFIG(object):
    X11_SOCKET_PATH_HOST = r'/tmp/.X11-unix'
    X11_SOCKET_PATH_GUEST = X11_SOCKET_PATH_HOST

    DISPLAY = os.environ.get('DISPLAY')

    IMAGE = r'arwmar/imgconv:devel'

class DEV_ENV_CONFIG(object):
    PATH = os.path.join(DOCKER_PATH, r'devel')
    
    IDE_LAUNCHER_PATH = r'qtcreator'

    SOURCES_PATH_HOST = PROJECT_PATH
    SOURCES_PATH_GUEST = r'/opt/sources/imgconv'

    HOME_PATH_HOST = os.path.join(PATH, r'home')
    HOME_PATH_GUEST = os.path.join(r'/home', LOGIN)
    
class ImgconvError(RuntimeError):
    pass

def run_cmd_noexcept(cmd, cwd=None):
    _cmd = ''
    if cwd:
        _cmd = 'cd "%s" && ' % cwd
    _cmd += cmd
    print "Running:", _cmd
    return subprocess.call(_cmd, shell=True)

def run_cmd(cmd, cwd=None):
    if run_cmd_noexcept(cmd, cwd) != 0:
        raise ImgconvError("Command failed [cwd=%s, cmd=%s]" % (cwd, cmd))

def docker_run_cmd(image, cmd, shared_folders=None, run_as_root=False, with_x=False):
    _cmd = 'docker run --rm' # --privileged'
    
    if shared_folders:
        _cmd += ' ' + ' '.join(['-v ' + ':'.join(sf) for sf in shared_folders])
    
    if not run_as_root:
        _cmd += ' --user=%d:%d' % (UID, GID)

    if with_x:
        if not os.path.exists(COMMON_CONFIG.X11_SOCKET_PATH_HOST) or not COMMON_CONFIG.DISPLAY:
            raise ImgconvError("X session not active?")
        _cmd += ' -v %s:%s' % (COMMON_CONFIG.X11_SOCKET_PATH_HOST, COMMON_CONFIG.X11_SOCKET_PATH_GUEST)
        _cmd += ' -e DISPLAY=%s' % COMMON_CONFIG.DISPLAY

    _cmd += ' %s %s' % (image, cmd)

    run_cmd(_cmd, DEV_ENV_CONFIG.PATH)

def is_docker_running():
    return run_cmd_noexcept(r'service docker status') == 0

def start_docker():
    run_cmd(r'sudo service docker start')

def user_exists(username):
    try:
        docker_run_cmd(COMMON_CONFIG.IMAGE, 'id %s' % username, run_as_root=True)
        return True
    except:
        return False

def run_ide():
    # xhost +local:`docker inspect --format='{{ .Config.Hostname }}' $containerId`
    run_cmd('xhost +')

    image = COMMON_CONFIG.IMAGE

    cmd = DEV_ENV_CONFIG.IDE_LAUNCHER_PATH

    shared_folders = [
        (DEV_ENV_CONFIG.SOURCES_PATH_HOST, DEV_ENV_CONFIG.SOURCES_PATH_GUEST),
        (DEV_ENV_CONFIG.HOME_PATH_HOST, DEV_ENV_CONFIG.HOME_PATH_GUEST),
    ]

    docker_run_cmd(image, cmd, shared_folders, with_x=True)

def main():
    if not is_docker_running():
        start_docker()
    return run_ide()
    
if __name__ == '__main__':
    sys.exit(main())
