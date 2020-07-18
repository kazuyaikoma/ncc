#!/bin/bash
assert() {
  exppected="$1"
  input="$2"

  cc -o ncc ncc.c
  ./ncc "$input" > tmp.s
  cc -o tmp tmp.s
  ./tmp
  actual="$?"

  if [ "$actual" == "$exppected" ]; then
    echo "$input => $actual"
  else
    echo "$input => $exppected expected, but got $actual"
    exit 1
  fi
}

assert 0 0
assert 42 42

echo OK
