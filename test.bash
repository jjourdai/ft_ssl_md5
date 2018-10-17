#!/bin/bash

make
echo test1
str="c5e433c1dbd7ba01e3763a9483e74b04"
result=$(echo "pickle rick" | ./ft_ssl md5)
if [ "$str" != "$result" ]
then
  echo "Not Same"
fi


echo test2
str="Do not pity the dead, Harry.
2d95365bc44bf0a298e09a3ab7b34d2f"
result=$(echo "Do not pity the dead, Harry." | ./ft_ssl md5 -p)
if [ "$str" != "$result" ]
then
  echo "Not Same"
fi

echo test3
str="e20c3b973f63482a778f3fd1869b7f25"
result=$(echo "Pity the living." | ./ft_ssl md5 -q -r)
if [ "$str" != "$result" ]
then
  echo "Not Same"
fi

echo test4
echo "And above all," > file
str="MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a"
result=$(./ft_ssl md5 file)
if [ "$str" != "$result" ]
then
  echo "Not Same"
fi

echo test5
str="53d53ea94217b259c11a5a2d104ec58a file"
result=$(./ft_ssl md5 -r file)
if [ "$str" != "$result" ]
then
  echo "Not Same"
fi

echo test6
str="MD5 (\"pity those that aren't following baerista on spotify.\") = a3c990a1964705d9bf0e602f44572f5f"
result=$(./ft_ssl md5 -s "pity those that aren't following baerista on spotify.")
if [ "$str" != "$result" ]
then
  echo "Not Same"
fi

echo test7
str="be sure to handle edge cases carefully
3553dc7dc5963b583c056d1b9fa3349c
MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a"
result=$(echo "be sure to handle edge cases carefully" | ./ft_ssl md5 -p file)
if [ "$str" != "$result" ]
then
  echo "Not Same"
fi

echo test8
str="MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a"
result=$(echo "some of this will not make sense at first" | ./ft_ssl md5 file)
if [ "$str" != "$result" ]
then
  echo "Not Same"
fi

echo test9
str="but eventually you will understand
dcdd84e0f635694d2a943fa8d3905281
53d53ea94217b259c11a5a2d104ec58a file"
result=$(echo "but eventually you will understand" | ./ft_ssl md5 -p -r file)
if [ "$str" != "$result" ]
then
  echo "Not Same"
fi

echo test10
str="GL HF let's go
d1e3cc342b6da09480b27ec57ff243e2
MD5 (\"foo\") = acbd18db4cc2f85cedef654fccc4a4d8
MD5 (file) = 53d53ea94217b259c11a5a2d104ec58a"
result=$(echo "GL HF let's go" | ./ft_ssl md5 -p -s "foo" file)
if [ "$str" != "$result" ]
then
  echo "Not Same"
fi

echo test11
str="one more thing
a0bd1876c6f011dd50fae52827f445f5
acbd18db4cc2f85cedef654fccc4a4d8 \"foo\"
53d53ea94217b259c11a5a2d104ec58a file
ft_ssl: md5: -s: No such file or directory
ft_ssl: md5: bar: No such file or directory"
echo "one more thing" | ./ft_ssl md5 -r -p -s "foo" file -s "bar" &> test
result=$(cat test)
rm test
if [ "$str" != "$result" ]
then
  echo "Not Same"
fi

echo test12
str="just to be extra clear
3ba35f1ea0d170cb3b9a752e3360286c
acbd18db4cc2f85cedef654fccc4a4d8
53d53ea94217b259c11a5a2d104ec58a"
result=$(echo "just to be extra clear" | ./ft_ssl md5 -r -q -p -s "foo" file)
if [ "$str" != "$result" ]
then
  echo "Not same"
fi

echo "https://www.youtube.com/watch?v=w-5yAtMtrSM" > big_smoke_order_remix
echo test13
str="a8dc621c3dcf18a8a2eddae1845e8e5f6498970a867056ac5f7121ac3d66cfd9"
result=$(./ft_ssl sha256 -q big_smoke_order_remix)
if [ "$str" != "$result" ]
then
  echo "Not same"
fi

echo test14
str="SHA256TEST (big_smoke_order_remix) = a8dc621c3dcf18a8a2eddae1845e8e5f6498970a867056ac5f7121ac3d66cfd9"
result=$(./ft_ssl sha256 big_smoke_order_remix)
if [ "$str" != "$result" ]
then
  echo "Not same"
fi

echo test15
str="SHA256TEST (\"wubba lubba dub dub\") = 23a0944d11b5a54f1970492b5265c732044ae824b7d5656acb193e7f0e51e5fa"
result=$(./ft_ssl sha256 -s "wubba lubba dub dub")
if [ "$str" != "$result" ]
then
  echo "Not same"
fi
