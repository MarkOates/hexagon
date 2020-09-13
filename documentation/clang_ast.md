## Clang AST Tooling

For more information on clang's AST tooling, follow this link to the
introduction: https://clang.llvm.org/docs/IntroductionToTheClangAST.html

To dump the AST of a file to the terminal, you may use a command like this:

```
clang -Xclang -ast-dump -fsyntax-only include/Hexagon/Logo.hpp -I../allegro_flare/include
```

Alternatively, any component of the above can be assembled programatically
within C++ using the `clang` llvm library (See https://github.com/llvm/llvm-project),

As written in the introduction, all information about the AST for a translation unit is bundled
up in the class [ASTContext](https://clang.llvm.org/doxygen/classclang_1_1ASTContext.html).
It allows traversal of the whole translation unit starting from
[getTranslationUnitDecl](https://clang.llvm.org/doxygen/classclang_1_1ASTContext.html#afad71d8f382bf1943bdd25fb89ebc32c),
or to access Clang’s [table of
identifiers](https://clang.llvm.org/doxygen/classclang_1_1ASTContext.html#a4f95adb9958e22fbe55212ae6482feb4)
for the parsed translation unit.
