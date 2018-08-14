all:
	@pwd
	@echo "Compilation..."
	@#en cas de confil decalage/reduction: voir option -v sur bison puis le
	@# fichier .output produit
	bison -d -o sources/compiler/compiler.c sources/compiler/language.y
	flex -o sources/compiler/lex.yy.c sources/compiler/token.l
	gcc -g sources/compiler/*.c -o bin/sortie
	@echo "Fait."
	rm sources/compiler/lex.yy.c
	rm sources/compiler/compiler.c
	rm sources/compiler/compiler.h
	@#echo "Compilation Var..."
	@#g++ sources/Var/*.cpp
	@#echo "Fait."
