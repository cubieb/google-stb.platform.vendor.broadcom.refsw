%{
   // build me with "flex -L -Ppp -olex.yy.c --never-interactive shader.l"
   // and delete the bogus #line directive at the start
   // --never-interactive is to avoid isatty declaration issues with c++

   #include "middleware/khronos/glsl/glsl_common.h"
   #include "middleware/khronos/glsl/glsl_errors.h"
   #include "middleware/khronos/glsl/glsl_intern.h"

   #include "middleware/khronos/glsl/prepro/glsl_prepro_directive.h"
   #include "middleware/khronos/glsl/prepro/glsl_prepro_token.h"

   #include "middleware/khronos/glsl/glsl_globals.h"
   #include "middleware/khronos/glsl/glsl_const_functions.h"
   #include "middleware/khronos/glsl/glsl_header.h"

   #include <stdlib.h>
   #include <string.h>

   TokenData pptoken;

   static int yyinput(char *buf, int buf_size);

   #undef YY_BUF_SIZE
   #define YY_BUF_SIZE 256
   #define YY_INPUT(buf,result,max_size) { result = yyinput(buf,(int)max_size); }

   extern void yyerror(char *c);

   /*
      disable unreachable code warning (break after return)
   */

#ifndef WIN32
#pragma off warn
#endif
%}

%option prefix="pp"
%option never-interactive
%option batch
%option nounistd
%option nounput
%option noyyalloc noyyrealloc noyyfree

IDENT    [_a-zA-Z][_a-zA-Z0-9]*
PPNUM    "."?[0-9]([0-9]|[_a-zA-Z]|[eEpP][+-]|".")*

DS       [0-9]+
EXP      [eE][-+]?{DS}
FRAC     {DS}"."{DS}|{DS}"."|"."{DS}

INTDEC   [1-9][0-9]*
INTOCT   "0"[0-7]*
INTHEX   "0"[xX][0-9a-fA-F]+

%x comment

%%
%{
   BEGIN INITIAL;
%}

   /*
      tokens for the preprocessor

      HASH
      WHITESPACE
      NEWLINE

      DEFINE
      UNDEF
      IFDEF
      IFNDEF
      ELIF
      ENDIF
      ERROR
      PRAGMA
      EXTENSION
      VERSION
      LINE

      ALL
      REQUIRE
      ENABLE
      WARN
      DISABLE
   */

"#"            return HASH;
[ \t]+         return WHITESPACE;
\n             {
                  g_LineNumber++;
                  return NEWLINE;
               }
\r             ;

"define"       { pptoken.s = glsl_intern("define", false); return DEFINE; }
"undef"        { pptoken.s = glsl_intern("undef", false); return UNDEF; }
"ifdef"        { pptoken.s = glsl_intern("ifdef", false); return IFDEF; }
"ifndef"       { pptoken.s = glsl_intern("ifndef", false); return IFNDEF; }
"elif"         { pptoken.s = glsl_intern("elif", false); return ELIF; }
"endif"        { pptoken.s = glsl_intern("endif", false); return ENDIF; }
"error"        { pptoken.s = glsl_intern("error", false); return _ERROR; }
"pragma"       { pptoken.s = glsl_intern("pragma", false); return PRAGMA; }
"extension"    { pptoken.s = glsl_intern("extension", false); return EXTENSION; }
"version"      { pptoken.s = glsl_intern("version", false); return VERSION; }
"line"         { pptoken.s = glsl_intern("line", false); return LINE; }

"all"          { pptoken.s = glsl_intern("all", false); return ALL; }
"require"      { pptoken.s = glsl_intern("require", false); return REQUIRE; }
"enable"       { pptoken.s = glsl_intern("enable", false); return ENABLE; }
"warn"         { pptoken.s = glsl_intern("warn", false); return WARN; }
"disable"      { pptoken.s = glsl_intern("disable", false); return DISABLE; }

   /*
      tokens for the shading language itself (keywords)

      ATTRIBUTE _CONST _BOOL _FLOAT _INT
      BREAK CONTINUE DO ELSE FOR IF DISCARD RETURN
      BVEC2 BVEC3 BVEC4 IVEC2 IVEC3 IVEC4 VEC2 VEC3 VEC4
      _MAT2 MAT3 MAT4 _IN _OUT INOUT UNIFORM VARYING
      SAMPLER2D SAMPLERCUBE
      STRUCT VOID WHILE
      INVARIANT
      HIGH_PRECISION MEDIUM_PRECISION LOW_PRECISION PRECISION
   */

"attribute"                return ATTRIBUTE;
"const"                    return _CONST;
"bool"                     return _BOOL;
"float"                    return _FLOAT;
"int"                      return _INT;
"break"                    return BREAK;
"continue"                 return CONTINUE;
"do"                       return DO;
"else"                     return ELSE;
"for"                      return FOR;
"if"                       return IF;
"discard"                  return DISCARD;
"return"                   return RETURN;
"bvec2"                    return BVEC2;
"bvec3"                    return BVEC3;
"bvec4"                    return BVEC4;
"ivec2"                    return IVEC2;
"ivec3"                    return IVEC3;
"ivec4"                    return IVEC4;
"vec2"                     return VEC2;
"vec3"                     return VEC3;
"vec4"                     return VEC4;
"mat2"                     return _MAT2;
"mat3"                     return MAT3;
"mat4"                     return MAT4;
"in"                       return _IN;
"out"                      return _OUT;
"inout"                    return INOUT;
"uniform"                  return UNIFORM;
"varying"                  return VARYING;
"sampler2D"                return SAMPLER2D;
"samplerExternalOES"       return SAMPLEREXTERNAL;
"samplerCube"              return SAMPLERCUBE;
"struct"                   return STRUCT;
"void"                     return _VOID;
"while"                    return WHILE;
"invariant"                return INVARIANT;
"highp"                    return HIGH_PRECISION;
"mediump"                  return MEDIUM_PRECISION;
"lowp"                     return LOW_PRECISION;
"precision"                return PRECISION;

   /*
      tokens for the shading language itself (punctuators)

      LEFT_OP RIGHT_OP
      INC_OP DEC_OP LE_OP GE_OP EQ_OP NE_OP
      LOGICAL_AND_OP LOGICAL_OR_OP LOGICAL_XOR_OP MUL_ASSIGN DIV_ASSIGN ADD_ASSIGN
      MOD_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN XOR_ASSIGN OR_ASSIGN
      SUB_ASSIGN
      LEFT_PAREN RIGHT_PAREN LEFT_BRACKET RIGHT_BRACKET LEFT_BRACE RIGHT_BRACE DOT
      COMMA COLON EQUAL SEMICOLON BANG DASH TILDE PLUS STAR SLASH PERCENT
      LEFT_ANGLE RIGHT_ANGLE BITWISE_OR_OP BITWISE_XOR_OP BITWISE_AND_OP QUESTION

      plus BCM2727 intrinsic functions
   */

"<<"           return LEFT_OP;
">>"           return RIGHT_OP;
"++"           return INC_OP;
"--"           return DEC_OP;
"<="           return LE_OP;
">="           return GE_OP;
"=="           return EQ_OP;
"!="           return NE_OP;
"&&"           return LOGICAL_AND_OP;
"||"           return LOGICAL_OR_OP;
"^^"           return LOGICAL_XOR_OP;
"*="           return MUL_ASSIGN;
"/="           return DIV_ASSIGN;
"+="           return ADD_ASSIGN;
"%="           return MOD_ASSIGN;
"<<="          return LEFT_ASSIGN;
">>="          return RIGHT_ASSIGN;
"&="           return AND_ASSIGN;
"^="           return XOR_ASSIGN;
"|="           return OR_ASSIGN;
"-="           return SUB_ASSIGN;
"("            return LEFT_PAREN;
")"            return RIGHT_PAREN;
"["            return LEFT_BRACKET;
"]"            return RIGHT_BRACKET;
"{"            return LEFT_BRACE;
"}"            return RIGHT_BRACE;
"."            return DOT;
","            return COMMA;
":"            return COLON;
"="            return EQUAL;
";"            return SEMICOLON;
"!"            return BANG;
"-"            return DASH;
"~"            return TILDE;
"+"            return PLUS;
"*"            return STAR;
"/"            return SLASH;
"%"            return PERCENT;
"<"            return LEFT_ANGLE;
">"            return RIGHT_ANGLE;
"|"            return BITWISE_OR_OP;
"^"            return BITWISE_XOR_OP;
"&"            return BITWISE_AND_OP;
"?"            return QUESTION;

"$$texture_2d_bias"     return INTRINSIC_TEXTURE_2D_BIAS;
"$$texture_2d_lod"      return INTRINSIC_TEXTURE_2D_LOD;
"$$texture_cube_bias"   return INTRINSIC_TEXTURE_CUBE_BIAS;
"$$texture_cube_lod"    return INTRINSIC_TEXTURE_CUBE_LOD;
"$$rsqrt"               return INTRINSIC_RSQRT;
"$$rcp"                 return INTRINSIC_RCP;
"$$log2"                return INTRINSIC_LOG2;
"$$exp2"                return INTRINSIC_EXP2;
"$$ceil"                return INTRINSIC_CEIL;
"$$floor"               return INTRINSIC_FLOOR;
"$$sign"                return INTRINSIC_SIGN;
"$$trunc"               return INTRINSIC_TRUNC;
"$$nearest"             return INTRINSIC_NEAREST;
"$$min"                 return INTRINSIC_MIN;
"$$max"                 return INTRINSIC_MAX;
"$$fmaxabs"             return INTRINSIC_MAXABS;
"$$fminabs"             return INTRINSIC_MINABS;

   /*
      reserved keywords which generate an error

      ASM
      CLASS UNION ENUM TYPEDEF TEMPLATE THIS PACKED
      GOTO SWITCH DEFAULT
      INLINE NOINLINE VOLATILE PUBLIC STATIC EXTERN EXTERNAL INTERFACE FLAT
      _LONG _SHORT DOUBLE HALF _FIXED _UNSIGNED SUPERP
      _INPUT OUTPUT
      HVEC2 HVEC3 HVEC4 DVEC2 DVEC3 DVEC4 FVEC2 FVEC3 FVEC4
      SAMPLER1D SAMPLER3D
      SAMPLER1DSHADOW SAMPLER2DSHADOW
      SAMPLER2DRECT SAMPLER3DRECT SAMPLER2DRECTSHADOW
      SIZEOF CAST
      NAMESPACE USING
   */

"asm"                      return ASM;
"class"                    return CLASS;
"union"                    return UNION;
"enum"                     return ENUM;
"typedef"                  return TYPEDEF;
"template"                 return TEMPLATE;
"this"                     return THIS;
"packed"                   return PACKED;
"goto"                     return GOTO;
"switch"                   return SWITCH;
"default"                  return DEFAULT;
"inline"                   return _INLINE;
"noinline"                 return NOINLINE;
"volatile"                 return VOLATILE;
"public"                   return PUBLIC;
"static"                   return STATIC;
"extern"                   return EXTERN;
"external"                 return EXTERNAL;
"interface"                return INTERFACE;
"flat"                     return FLAT;
"long"                     return _LONG;
"short"                    return _SHORT;
"double"                   return DOUBLE;
"half"                     return HALF;
"fixed"                    return _FIXED;
"unsigned"                 return _UNSIGNED;
"superp"                   return SUPERP;
"input"                    return _INPUT;
"output"                   return OUTPUT;
"hvec2"                    return HVEC2;
"hvec3"                    return HVEC3;
"hvec4"                    return HVEC4;
"dvec2"                    return DVEC2;
"dvec3"                    return DVEC3;
"dvec4"                    return DVEC4;
"fvec2"                    return FVEC2;
"fvec3"                    return FVEC3;
"fvec4"                    return FVEC4;
"sampler1D"                return SAMPLER1D;
"sampler3D"                return SAMPLER3D;
"sampler1DShadow"          return SAMPLER1DSHADOW;
"sampler2DShadow"          return SAMPLER2DSHADOW;
"sampler2DRect"            return SAMPLER2DRECT;
"sampler3DRect"            return SAMPLER3DRECT;
"sampler2DRectShadow"      return SAMPLER2DRECTSHADOW;
"sizeof"                   return SIZEOF;
"cast"                     return CAST;
"namespace"                return NAMESPACE;
"using"                    return USING;

   /*
      boolean constants, preprocessing number and identifier

      TRUE FALSE
      PPNUMBER
      IDENTIFIER
   */

"true"  return _TRUE;
"false" return _FALSE;

{FRAC}{EXP}?|{DS}{EXP} {
                          // Cast from double and then copy bits.
                          pptoken.f = float_to_bits((float)atof(pptext));
                          pptoken.s = strdup_fast(pptext);
                          return PPNUMBERF;
                       }

{INTDEC}|{INTOCT}|{INTHEX} {
                              // Base of 0 does automatic dec/oct/hex recognition.
                              pptoken.i = (const_int)strtol(yytext, (char**)NULL, 0);
                              pptoken.s = strdup_fast(pptext);
                              return PPNUMBERI;
                           }

{PPNUM} {
           pptoken.s = strdup_fast(pptext);
           return PPNUMBERU;
        }
{IDENT} {
           pptoken.s = glsl_intern(pptext, true);
           return IDENTIFIER;
        }

   /*
      C++ comment
   */

"//".*   return WHITESPACE;

   /*
      C comment
   */

"/*"     BEGIN(comment);

<comment>[^*\n]*        /* eat anything that's not a '*' */
<comment>"*"+[^*/\n]*   /* eat up '*'s not followed by '/'s */
<comment>\n             g_LineNumber++;
<comment>"*"+"/"        {
                           BEGIN(INITIAL);
                           return WHITESPACE;
                        }
<comment><<EOF>>        glsl_compile_error(ERROR_LEXER_PARSER, 1, g_LineNumber, "unexpected end of file in comment");

.       {
           pptoken.s = strdup_fast(pptext);
           return UNKNOWN;
        }

%%

static struct ShaderSource {
   int         Count;
   const char *const *Values;
   const char *CurrentPosition;
   int         Index;
} s_ShaderSource;
static YY_BUFFER_STATE s_CurrentBufferState;
static bool including = false;

// When the lexer starts, set it to read the header.
void glsl_init_lexer(int sourcec, const char * const *sourcev)
{
   g_LineNumber = LINE_NUMBER_UNDEFINED;
   g_FileNumber = -1;

   s_ShaderSource.Count = sourcec;
   s_ShaderSource.Values = sourcev;

   s_ShaderSource.Index           =  -1;
   s_ShaderSource.CurrentPosition = "";

   // Create buffer to use with YY_INPUT
   s_CurrentBufferState = pp_create_buffer(NULL, YY_BUF_SIZE - 2);
   pp_switch_to_buffer(s_CurrentBufferState);
}

void glsl_include(const char *s)
{
    /* We don't support including from inside an include */
    vcos_assert(!including);
    pppush_buffer_state(s_CurrentBufferState);
    pp_scan_string(s);
    including = true;
}

void glsl_term_lexer(void)
{
   pplex_destroy();
}

void * ppalloc (size_t bytes)
{
   uint32_t *result = (uint32_t *)glsl_fastmem_malloc(bytes + sizeof(uint32_t), true);
   result[0] = (uint32_t)bytes;
   return result + 1;
}

void * pprealloc (void * ptr, size_t bytes)
{
   size_t old_bytes = ptr ? (size_t)((uint32_t *)ptr)[-1] : 0;
   void *result = ppalloc(bytes);
   memcpy(result, ptr, bytes < old_bytes ? bytes : old_bytes);
   return result;
}

void ppfree (void * ptr) {
   UNUSED(ptr);
   /* Do nothing */
}

// When the current buffer is depleted, switch to the next string.
// Returning 1 causes the lexer to terminate; 0 causes it to try again.
// This allows you to switch buffers.
int ppwrap(void)
{
   if (including) {
      pppop_buffer_state();
      including = false;
      return 0;
   }
   return 1;         // EOF
}

// If we have reached the end of current source buffer, move to the next one. This may reset the line number.
static void pp_ensure_source()
{
   /*
      Look to next buffer. We have

      g_ShaderSourceCurrentIndex                   string in progress
      -1                                           sampler functions
      0                                           first shader source
      :     :     :
      g_ShaderSourceCount-1                       last shader source
      g_ShaderSourceCount                         \n
      g_ShaderSourceCount+1                       last constant function
      :     :     :
      g_ShaderSourceCount+CONST_FUNCTION_COUNT    first constant function
   */

   while (*s_ShaderSource.CurrentPosition == '\0') {
      g_LineNumber = 1;

      if (s_ShaderSource.Index == -1) {
         s_ShaderSource.CurrentPosition = sampler_functions;
      } else {
         if (s_ShaderSource.Index < s_ShaderSource.Count) {
            if (s_ShaderSource.Index == 0) {
               glsl_directive_allow_version();
               glsl_directive_allow_extension();
            }
            s_ShaderSource.CurrentPosition = s_ShaderSource.Values[s_ShaderSource.Index];
            g_FileNumber++;
         } else if (s_ShaderSource.Index == s_ShaderSource.Count) {
            glsl_directive_reset_macros();
            s_ShaderSource.CurrentPosition = "\n";
         } else if (s_ShaderSource.Index < s_ShaderSource.Count+CONST_FUNCTION_COUNT) {
            bool seen = false;
            int i;
            // count down from the largest to smallest
            for (i = s_ShaderSource.Count+CONST_FUNCTION_COUNT-s_ShaderSource.Index; i >= 0; i--, s_ShaderSource.Index++) {
               const char *body = constantFunctions[i].u.function_instance.const_function_body;
               seen = constantFunctions[i].u.function_instance.const_function_body_seen;
               if (seen) {
                  s_ShaderSource.CurrentPosition = body;
                  break;
               }
            }
         } else {
            return;
         }
      }

      s_ShaderSource.Index++;
   }
}

// Helper method to skip given character from the source.
static int pp_consume(char c)
{
   // ensure that we have data to read, this may reset the line number
   pp_ensure_source();
   if (*s_ShaderSource.CurrentPosition == c) {
      // skip the consumed character
      s_ShaderSource.CurrentPosition++;
      return 1;
   }
   return 0;
}

// Called by flex to get more input
static int yyinput(char* buf, int buf_size)
{
   int num = 0;

   // Check whether there is unprocessed new-line buffered in flex.
   // Flex requires at least one lookahead character before it commits to token's action
   // so this happens reasonably frequently and it breaks our line numbering.
   if (YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[0] == '\n' && &YY_CURRENT_BUFFER_LVALUE->yy_ch_buf[1] == buf) {
      // \r is not used for anything in the lexer, so use it to flush the buffer
      buf[num++] = '\r';
      return num;
   }

   // Consume all line continuations here so that the lexer does not even see them.
   // Note that single line continuation may be split among multiple source buffers.
   // Line number modification is fine here because the lexer has already processed
   // all previous (complete) tokens at this point (new-lines in particular).
   // GLSL ES 1.0.17: The line continuation character (\) is not part of the language.
   // GLSL ES 3.00.4: Backslash ('\'), used to indicate line continuation when immediately preceding a new-line.
   while (pp_consume('\\')) {
      if (1 /* Only ES2.0 supported */) {
         // Line continuations are not supported before 3.0
         // #version should have been processed by now
         buf[num++] = '\\';
         break;
      } else if (pp_consume('\n')) {
         g_LineNumber++;
         if (pp_consume('\r') && g_LineNumber == 1)
            g_LineNumber++; // do again if line number was just reset
      } else if (pp_consume('\r')) {
         g_LineNumber++;
         if (pp_consume('\n') && g_LineNumber == 1)
            g_LineNumber++; // do again if line number was just reset
      } else {
         // the backslash did not start line continuation so pass it to the lexer
         buf[num++] = '\\';
         break;
      }
   }

   pp_ensure_source();

   // Copy chunk of data to flex's buffer until we see something that needs to handled in this method
   // (end of current source buffer or line continuation).
   // Flex will process this buffer and call yyinput again once it is done with it.
   while (*s_ShaderSource.CurrentPosition != '\0' && *s_ShaderSource.CurrentPosition != '\\' && num < buf_size) {
      // Turn any \r, \n or pair into \n.
      // GLSL ES 1.0 & 3.0: [Lines] are terminated by carriage-return or line-feed. If both are used together, it will count as only a single line termination.
      char c = *(s_ShaderSource.CurrentPosition++);
      if (c == '\n' || c == '\r') {
         char c2 = *s_ShaderSource.CurrentPosition;
         if ((c == '\n' && c2 == '\r') || (c == '\r' && c2 == '\n'))
            s_ShaderSource.CurrentPosition++; // skip the other one

         buf[num++] = '\n';
      } else {
         buf[num++] = c;
      }
   }

   return num;
}