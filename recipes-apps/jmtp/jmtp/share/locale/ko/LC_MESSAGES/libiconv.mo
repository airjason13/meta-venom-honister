??    /      ?  C           C     9   ]  o   ?  B     m   J  ?   ?  \   ?  ;   U  P   ?  [   ?     >  @   A  N   ?  J   ?  D     d   a  ?   ?  :   a	     ?	     ?	     ?	  0   ?	     ?	  5   
  	   ;
     E
  ?   Z
  )     "   .  1   Q  <   ?  &   ?  A   ?  ;   )     e  /   u  7   ?  3   ?  :     ;   L  $   ?     ?     ?     ?     ?  2     ?  :  S     I   i  u   ?  I   )  p   s  :   ?  `     =   ?  D   ?  ^        b  V   e  `   ?  Z     E   x  ^   ?  X     <   v     ?     ?     ?  /   ?        L   /     |     ?  ?   ?     ~     ?      ?  Y   ?  7   5  R   m  Q   ?       I   )  P   s  M   ?  S     T   f  7   ?  3   ?  9   '     a     u  8   ?           -                	   .          '                  
   !   ,                       )          &               #                         "           /                            %          (                $      *   +                --byte-subst=FORMATSTRING   substitution for unconvertible bytes
   --help                      display this help and exit
   --unicode-subst=FORMATSTRING
                              substitution for unconvertible Unicode characters
   --version                   output version information and exit
   --widechar-subst=FORMATSTRING
                              substitution for unconvertible wide characters
   -c                          discard unconvertible characters
   -f ENCODING, --from-code=ENCODING
                              the encoding of the input
   -l, --list                  list the supported encodings
   -s, --silent                suppress error messages about conversion problems
   -t ENCODING, --to-code=ENCODING
                              the encoding of the output
 %s %s argument: A format directive with a size is not allowed here. %s argument: A format directive with a variable precision is not allowed here. %s argument: A format directive with a variable width is not allowed here. %s argument: The character '%c' is not a valid conversion specifier. %s argument: The character that terminates the format directive is not a valid conversion specifier. %s argument: The format string consumes more than one argument: %u argument. %s argument: The format string consumes more than one argument: %u arguments. %s argument: The string ends in the middle of a directive. %s: I/O error %s:%u:%u %s:%u:%u: cannot convert %s:%u:%u: incomplete character or shift sequence (stdin) Converts text from one encoding to another encoding.
 I/O error Informative output:
 License GPLv3+: GNU GPL version 3 or later <%s>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
 Options controlling conversion problems:
 Options controlling error output:
 Options controlling the input and output format:
 Report bugs in the bug tracker at <%s>
or by email to <%s>.
 Try '%s --help' for more information.
 Usage: %s [OPTION...] [-f ENCODING] [-t ENCODING] [INPUTFILE...]
 Usage: iconv [-c] [-s] [-f fromcode] [-t tocode] [file ...] Written by %s.
 cannot convert byte substitution to Unicode: %s cannot convert byte substitution to target encoding: %s cannot convert byte substitution to wide string: %s cannot convert unicode substitution to target encoding: %s cannot convert widechar substitution to target encoding: %s conversion from %s to %s unsupported conversion from %s unsupported conversion to %s unsupported or:    %s -l
 or:    iconv -l try '%s -l' to get the list of supported encodings Project-Id-Version: libiconv 1.17-pre1
Report-Msgid-Bugs-To: bug-gnu-libiconv@gnu.org
PO-Revision-Date: 2022-02-14 15:09+0900
Last-Translator: Seong-ho Cho <darkcircle.0426@gmail.com>
Language-Team: Korean <translation-team-ko@googlegroups.com>
Language: ko
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
X-Bugs: Report translation errors to the Language-Team address.
Plural-Forms: nplurals=1; plural=0;
X-Generator: Poedit 2.3.1
   --byte-subst=<형식문자열>   변환 불가 바이트 문자의 대체 문자
   --help                      이 도움말을 표시하고 나갑니다
   --unicode-subst=<형식문자열>
                              변환 불가 유니코드 문자의 대체 문자
   --version                   버전 정보를 출력하고 나갑니다
   --widechar-subst=<형식문자열>
                              변환 불가 전각 문자의 대체 문자
   -c                          변환 불가 문자 무시
   -f <인코딩>, --from-code=<인코딩>
                              입력 인코딩 형식
   -l, --list                  지원 인코딩 목록 출력
   -s, --silent                변환 문제 오류 메시지 숨김
   -t <인코딩>, --to-code=<인코딩>
                              출력 인코딩 형식
 %s %s 인자: 크기 정보를 가진 형식 지정자를 여기에 둘 수 없습니다. %s 인자: 변수 정밀도 정보를 가진 형식 지정자를 여기에 둘 수 없습니다. %s 인자: 변수 폭 정보를 가진 형식 지정자를 여기에 둘 수 없습니다. %s 인자: '%c' 문자는 올바른 변환 지정자가 아닙니다. %s 인자: 형식 지정자를 끝내는 문자는 올바른 변환 지정자가 아닙니다. %s 인자: 형식 문자열이 하나 이상의 인자에 해당합니다: 인자 %u개. %s 인자: 문자열이 지정자 중간에서 끝납니다. %s: 입출력 오류 %s:%u:%u %s:%u:%u: 변환할 수 없음 %s:%u:%u: 미결 문자 또는 시퀀스 밀림 (표준입력) 텍스트를 지정 인코딩에서 다른 인코딩으로 변환합니다.
 입출력 오류 정보 출력:
 GPLv3+ 라이선스: GNU GPL 버전 3 이상 <%s>
이 프로그램은 자유 소프트웨어입니다: 자유롭게
바꾸고 재배포할 수 있습니다.
법률이 허용하는 모든 범위내의 보증은 없습니다.
 변환 문제 제어 옵션:
 오류 출력 제어 옵션:
 입출력 형식 제어 옵션:
 <%s> 문제 추적 사이트 또는 <%s> 메일 주소에 
버그를 알려주십시오.
 자세한 정보는 '%s --help'를 입력하십시오.
 사용법: %s [<옵션>...] [-f <인코딩>] [-t <인코딩>] [<입력파일>...]
 사용법: iconv [-c] [-s] [-f <목적코드>] [-t <대상코드>] [<파일> ...] %s이(가) 작성함.
 바이트 대체 요소를 유니코드로 변환할 수 없습니다: %s 바이트 대체 요소를 대상 인코딩으로 변환할 수 없습니다: %s 바이트 대체 요소를 전각 문자열로 변환할 수 없습니다: %s 유니코드 대체 요소를 대상 인코딩으로 변환할 수 없습니다: %s 전각 문자 대체 요소를 대상 인코딩으로 변환할 수 없습니다: %s %s → %s 인코딩 변환을 지원하지 않습니다 %s 인코딩의 변환을 지원하지 않습니다 %s 인코딩으로의 변환을 지원하지 않습니다   또는:    %s -l
   또는:    iconv -l 지원 인코딩 목록은 '%s -l'을 입력하십시오 