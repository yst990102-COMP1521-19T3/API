CC	?= clang
CFLAGS	?= -O3 -fvisibility=hidden
LDFLAGS	?= -s -static

ACTIVITY = emu

.PHONY: all
all:	${ACTIVITY}

#
# We can't build in prod:public, because the rsync(1) from prod:private
# drops the solutions -- and apparently the binaries too.  Instead, copy
# it across from prod:private.
#
ifeq (,$(findstring /public/, $(realpath ${PWD})))
${ACTIVITY}:	solutions/*.c
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^
else
PRIVATE_DIR	= ../../../private

${ACTIVITY}:	${PRIVATE_DIR}/activities/${ACTIVITY}/${ACTIVITY}
	install $< -m 755 $@
endif

.PHONY:	clean
clean:
	-rm -f ${ACTIVITY}
