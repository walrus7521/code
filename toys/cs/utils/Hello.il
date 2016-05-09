// C:\Windows\Microsoft.NET\Framework64\v4.0.30319\ilasm.exe
// http://www.i-programmer.info/programming/other-languages/933-getting-started-with-il.html

.assembly extern mscorlib {}
.assembly Hello {}
.module Hello.exe

.class Hello.Program
extends [mscorlib]System.Object
{
 .method static void Main(string[] args)
 cil managed
 {
  .entrypoint
  ldstr "Hello World"
  call void [mscorlib]System.Console::
  WriteLine(string)
  ret
 }
}
