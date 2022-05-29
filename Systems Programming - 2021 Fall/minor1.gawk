{
while (getline == 1) {
if($0 >= 0) {
printf("%6d\t\t%3d\n",$0,($0%360));
}
else {
printf("%6d\t\t%3d\n",$0,($0%360)+360);
}
}
}