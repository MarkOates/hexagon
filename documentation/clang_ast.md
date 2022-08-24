## Clang AST Tooling


Update: Clang AST can also be used more comprehensively used with
`clang-check`, which is available with brew:

```
brew install llvm
```

At that point, `clang-check` will be located in your homebrew folder (because
homebrew does not want to overwrite the symlink for `clang`, `clang++`, etc.
programs that come already pre-installed on MacOS.).  You can use the homebrew
`clang-check` like this:

```
/opt/homebrew/opt/llvm/bin/clang-check -ast-dump-filter=Hexagon::Logo -ast-dump include/Hexagon/Logo.hpp
```

It also appears at this time that `clang` (below) does not support
`-ast-dump-filter`, and `clang-check` does not support `-ast-dump=json`.

## Clang AST Tooling

For more information on clang's AST tooling, follow this link to the
introduction: https://clang.llvm.org/docs/IntroductionToTheClangAST.html

To dump the AST of a file to the terminal, you may use a command like this:

```
clang -Xclang -ast-dump -fsyntax-only include/Hexagon/Logo.hpp -I../allegro_flare/include
```

Clang can also output the format in JSON by adding the argument to `-ast-dump=json`
```
clang -Xclang -ast-dump=json -fsyntax-only -ast-dump-filter=Hexagon::Logo include/Hexagon/Logo.hpp -I../allegro_flare/include
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
