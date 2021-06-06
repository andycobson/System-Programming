# Andrew Jacobson asj0108
s/^\([0-9]{3}\) /\(800\) /g
s/[()]//g
s/([0-9]{3}) ([0-9]{3})-([0-9]{4})/\1-\2-\3/g
s/([0-9]{5})-([0-9]{4})/\1-1234/g
s/^(Lois) \<Lane\>/\1 Kent/g
s/([A-Za-z0-9]+) ([A-Za-z0-9]+) \<Lane\>/\1 \2 Ln/g
s/ ([0-9]{3})-([0-9]{3})-([0-9]{4})./ \2-\1-\3./g
s/ @([0-9]{3})/ #\1/g
s/^([A-Za-z]+); /\1, /g
$a p.s. your winnings must be claimed by February 29th.
