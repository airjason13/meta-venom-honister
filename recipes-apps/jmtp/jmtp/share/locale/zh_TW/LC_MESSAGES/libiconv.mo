��    /      �  C           C     9   ]  o   �  B     m   J  ?   �  \   �  ;   U  P   �  [   �     >  @   A  N   �  J   �  D     d   a  �   �  :   a	     �	     �	     �	  0   �	     �	  5   
  	   ;
     E
  �   Z
  )     "   .  1   Q  <   �  &   �  A   �  ;   )     e  /   u  7   �  3   �  :     ;   L  $   �     �     �     �     �  2     �  :  G     =   ]  h   �  =     c   B  :   �  N   �  4   0  F   e  L   �     �  9   �  B   6  ?   y  4   �  E   �  B   4  *   w     �     �     �  /   �       4        O     b  �   |     &     F  (   f  I   �  .   �  ?     I   H     �  ,   �  /   �  ,   �  /   *  /   Z     �     �     �     �     �  +   �           -                	   .          '                  
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
PO-Revision-Date: 2022-02-16 00:25+0800
Last-Translator: Yi-Jyun Pan <pan93412@gmail.com>
Language-Team: Chinese (traditional) <zh-l10n@lists.linux.org.tw>
Language: zh_TW
MIME-Version: 1.0
Content-Type: text/plain; charset=UTF-8
Content-Transfer-Encoding: 8bit
Plural-Forms: nplurals=1; plural=0;
X-Bugs: Report translation errors to the Language-Team address.
X-Generator: Poedit 3.0.1
   --byte-subst=格式字串       做為無法轉換的替代位元組
   --help                      顯示這份說明然後離開
   --unicode-subst=格式字串
                              做為無法轉換的萬國碼替代字元
   --version                   輸出版本資訊然後離開
   --widechar-subst=格式字串
                              做為無法轉換的替代寬字元
   -c                          捨棄無法轉換的字元
   -f 編碼, --from-code=編碼
                              輸入的編碼
   -l, --list                  清單支援的編碼
   -s, --silent                抑制關於轉換問題的錯誤訊息
   -t 編碼, --to-code=編碼
                              輸出的編碼
 %s %s 引數：這裡不允許具備大小的格式指令。 %s 引數：這裡不允許具備可變精確度的格式指令。 %s 引數：這裡不允許具備可變寬度的格式指令。 %s 引數：字元 %c 並非有效的轉換符號。 %s 引數：終止格式指令的字元並非有效的轉換符號。 %s 引數：格式字串耗用超過一個引數：%u 個引數。 %s 引數：字串結束於指令中間。 %s：輸入輸出錯誤 %s:%u:%u %s:%u:%u：無法轉換 %s:%u:%u：不完整的字元或是換碼序列 (標準輸入) 將文字從一種編碼轉換到另一種編碼。
 輸入輸出錯誤 詳細資訊的輸出：
 授權 GPLv3+: GNU GPL 第三版或後續版本 <%s>
這是自由軟體：您可以自由變更和再次散布它。
在法律所允許的範圍內不做任何擔保。
 控制轉換問題的選項：
 控制錯誤輸出的選項：
 控制輸入與輸出格式的選項：
 在臭蟲追蹤器 <%s> 回報臭蟲
或者是寄電子信件到 <%s>。
 嘗試「%s --help」以獲得更多資訊。
 用法：%s [選項…] [-f 編碼] [-t 編碼] [輸入檔…]
 用法：iconv [-c] [-s] [-f 來源編碼] [-t 目的編碼] [檔案 …] 作者 %s。
 無法轉換替代位元組到萬國碼：%s 無法轉換替代位元組到目標編碼：%s 無法轉換替代位元組到寬字串：%s 無法轉換替代萬國碼到目標編碼：%s 無法轉換替代寬字元到目標編碼：%s 不支援從 %s 轉換到 %s 不支援從 %s 進行轉換 不支援轉換到 %s 或：   %s -l
 或：  iconv -l 嘗試 %s -l 以獲得支援的編碼清單 