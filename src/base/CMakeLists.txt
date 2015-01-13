set(HDRS
    exception.h
    log.h
    message_loop.h
    thread.h
    task.h
    waitable_event.h
  assert.h
   )

set(SRCS
    exception.cc
    log.cc
    message_loop.cc
    thread.cc
    waitable_event.cc
    task_queue.cc
   )

add_library(${TARGET_BASE} SHARED ${SRCS} ${HDRS})
target_link_libraries(${TARGET_BASE} ${Boost_LIBRARIES})
set_target_properties(${TARGET_BASE} PROPERTIES COMPILE_FLAGS "-fPIC")
