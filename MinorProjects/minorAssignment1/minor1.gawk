# Andrew Jacobson    asj0108
BEGIN { printf("Student Average Test Scores\nName %20s\n","Average") }
{ FS="," }
NR > 1 && $3=="A" {  printf("%s %-12s %.1f\n",$2,$1, ($4+$5+$6)/3)
	active = active + 1 
	total = total + ($4+$5+$6)/3}
END {printf("%d Students with average score of %.1f\n", active, total/active) }
