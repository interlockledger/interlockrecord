#!/bin/bash

DOC_TREE="
		docs
		docs/02-fases-posteriores-ao-projeto
		docs/99-acompanhamento-e-controle
		docs/99-acompanhamento-e-controle/documentos-enviados-ao-cliente
		docs/99-acompanhamento-e-controle/pautas-e-atas-de-reuniao
		docs/99-acompanhamento-e-controle/controles
		docs/99-acompanhamento-e-controle/gestao-de-mudancas
		docs/99-acompanhamento-e-controle/cronograma
		docs/99-acompanhamento-e-controle/informes-e-comunicados
		docs/99-acompanhamento-e-controle/acompanhamento
		docs/98-documentos-entregues-pelo-cliente
		docs/01-projeto
		docs/01-projeto/01-inicio
		docs/01-projeto/04-construcao
		docs/01-projeto/04-construcao/manuais
		docs/01-projeto/06-encerramento
		docs/01-projeto/05-transicao
		docs/01-projeto/02-visao-de-negocio
		docs/01-projeto/02-visao-de-negocio/processos-de-negocio
		docs/01-projeto/03-elaboracao
		docs/01-projeto/03-elaboracao/documentos-tecnicos
		docs/01-projeto/03-elaboracao/casos-de-uso
		docs/01-projeto/03-elaboracao/casos-de-teste"
SRC_DIRS="
		prototypes
		build
		programs
		deps
		web
		tools
		libs
		databases
		install"

function create_dir() {
	local dirName=$1
	local ignoreName=$dirName/.gitignore

	if [ -d $dirName ]; then
		echo "$dirName already exists."
	else
		mkdir -p $dirName
		echo "$dirName created."
	fi
	if [ -f $ignoreName ]; then
		echo "$ignoreName already exists."
	else
		echo "" > $ignoreName
		echo "$ignoreName created."
	fi
}

function make_docs() {
	for d in `echo $DOC_TREE`; do
		create_dir $d
	done
}

function make_src() {
	local prefix=""

	if [ -z "$1" ]; then
		prefix="src"
	else
		prefix="src-$1"
	fi

	echo $prefix
	for d in `echo $SRC_DIRS`; do
		create_dir "$prefix/$d"
	done
}

function print_help() { 
	echo "make-tree.sh - 0.1"
	echo "OpenCS source tree creation tool"
	echo "Copyright (c) Open Communications Security S.A.. All rights reserved."
	echo ""
	echo "Usage:"
	echo "   make-tree.sh docs"
    echo "      Creates the documentation tree."
	echo "   make-tree.sh src"
    echo "      Creates the default src code tree."
	echo "   make-tree.sh src <name>"
    echo "      Creates the src-<name> code tree."
	echo ""
}

# Main
case "$1" in
docs)
	make_docs
	;;
src)
	make_src "$2"
	;;
**)
	print_help
	exit 1
	;;
esac

