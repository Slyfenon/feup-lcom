# name of the program (Minix service)
PROG=proj

.PATH: ${.CURDIR}
.PATH: ${.CURDIR}/devices/graphics
.PATH: ${.CURDIR}/devices/kbc
.PATH: ${.CURDIR}/devices/timer
.PATH: ${.CURDIR}/game

# source code files to be compiled
SRCS = proj.c keyboard.c mouse.c graphics.c utils.c event_handler.c game.c sprite.c target.c position.h timer.c

# additional compilation flags
# "-Wall -Wextra -Werror -I . -std=c11 -Wno-unused-parameter" are already set
CPPFLAGS += -pedantic -DPROJ

# list of library dependencies (for Lab 2, only LCF library)
DPADD += ${LIBLCF}
LDADD += -llcf

# include LCOM's makefile that does all the "heavy lifting"
.include <minix.lcom.mk>
