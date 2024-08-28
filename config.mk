NAME:=clulang
VERSION:=0.1.0
BUILD:=.build
ODIR:=$(BUILD)/cache

FLAGS:=-Wall -Wextra -pedantic -std=c++20 -ggdb
DEFINE:=-DNAME='"$(NAME)"' -DVERSION='"$(VERSION)"'
LDFLAGS:=
