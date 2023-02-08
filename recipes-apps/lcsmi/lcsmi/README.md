version:221003_01
log:
    1. add reboot for delay 2 secs while get reboot in alive broadcast

remove the CFLAG in .mk file
Need to check why the CFALG will produce compile error as below
| utildbg.c:271:32: error: invalid use of undefined type 'struct tm'
| utildbg.c:272:32: error: invalid use of undefined type 'struct tm'
| utildbg.c:273:33: error: invalid use of undefined type 'struct tm'

