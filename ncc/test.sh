#!/bin/bash
assert() {
  exppected="$1"
  input="$2"

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
assert 21 '5+20-4'
assert 41 '12 + 34 - 5'
assert 47 '5 + 6 * 7'

assert 15 '5 * (9 - 6)'
assert 4 '(3 + 5) / 2'

assert 10 '-10+20'
assert 10 '- -10'
assert 16 '-2*(-3-5)'

assert 0 '0 == 1'
assert 1 '0 != 1'
assert 1 '51 == 51'
assert 0 '42 == 51'

assert 1 '-1 < 2'
assert 0 '2 < 1'
assert 1 '2 > 0'
assert 0 '2 > 3'

assert 1 '1 >= 0'
assert 1 '1 >= 1'
assert 1 '1 <= 1'
assert 0 '1 <= 0'

make clean

ESC=$(printf '\033')
echo "${ESC}[32mOK${ESC}[m"
