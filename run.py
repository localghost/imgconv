#!/usr/bin/env python

import os
import sys
import pwd

PROJECT_PATH = os.path.dirname(os.path.realpath(__file__))
DOCKER_PATH = os.path.join(PROJECT_PATH, r'docker')

class COMMON_CONFIG(object):
    X11_SOCKET_PATH_HOST = r'/tmp/.X11-unix'
    X11_SOCKET_PATH_GUEST = X11_SOCKET_PATH_HOST

    RUN_AS_UID = os.getuid()
    RUN_AS_GID = os.getgid()

    DISPLAY = os.environ.get('DISPLAY')

    IMAGE = r'arwmar/imgconv:devel'

class DEV_ENV_CONFIG(object):
    PATH = os.path.join(DOCKER_PATH, r'devel')
    
    IDE_LAUNCHER_PATH = r'/opt/qtcreator/bin/qtcreator'

    SOURCES_PATH_HOST = PROJECT_PATH
    SOURCES_PATH_GUEST = r'/opt/sources/imgconv'

    HOME_PATH_HOST = os.path.join(PATH, r'home')
    HOME_PATH_GUEST = os.path.join(r'/home', pwd.getpwuid(COMMON_CONFIG.RUN_AS_UID)[0])
    
class ImgconvError(RuntimeError):
    pass

def run_cmd(cmd, cwd=None):
    _cmd = ''
    if cwd:
        _cmd = 'cd "%s" && ' % cwd
    _cmd += cmd
    print "Running:", _cmd
    if os.system(_cmd) != 0:
        raise ImgconvError("Command failed: " + _cmd)

def docker_run_cmd(image, cmd, shared_folders=None, run_as_root=False, with_x=False):
    _cmd = 'docker run --rm'
    
    if shared_folders:
        _cmd += ' ' + ' '.join(['-v ' + ':'.join(sf) for sf in shared_folders])
    
    if not run_as_root:
        _cmd += ' --user=%d:%d' % (COMMON_CONFIG.RUN_AS_UID, COMMON_CONFIG.RUN_AS_GID)

    if with_x:
        if not os.path.exists(COMMON_CONFIG.X11_SOCKET_PATH_HOST) or not COMMON_CONFIG.DISPLAY:
            raise ImgconvError("X session not active?")
        _cmd += ' -v %s:%s' % (COMMON_CONFIG.X11_SOCKET_PATH_HOST, COMMON_CONFIG.X11_SOCKET_PATH_GUEST)
        _cmd += ' -e DISPLAY=%s' % COMMON_CONFIG.DISPLAY

    _cmd += ' %s %s' % (image, cmd)

    run_cmd(_cmd, DEV_ENV_CONFIG.PATH)

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
    return run_ide()
    
if __name__ == '__main__':
    sys.exit(main())
