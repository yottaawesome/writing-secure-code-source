# ExerciseArgs.pl

# Change as you see fit.
my $exe = "process.exe";
my $iterations = 100;

# Possible option types
my $NUMERIC = 0;
my $ALPHANUM = 1;
my $PATH = 2;

# Hash of all options and types
# /p is a path, /i is numeric, and /n is alphanum.
my %opts = (
    p => $PATH,
    i => $NUMERIC,
    n => $ALPHANUM);

# Do tests.
for (my $i = 0; $i < $iterations; $i++) {
    print "Iteration $i";

    # How many args to pick?
    my $numargs = 1 + int rand scalar %opts;
    print " ($numargs args) ";

    # Build array of option names.
    my @opts2 = ();
    foreach (keys %opts) {
        push @opts2, $_;
    }

    # Build args string.
    my $args = "";
    for (my $j = 0; $j < $numargs; $j++) {
        my $whicharg = @opts2[int rand scalar @opts2];
        my $type = $opts{$whicharg};

        my $arg = "";
        $arg = getTestNumeric() if $type == $NUMERIC;
        $arg = getTestAlphaNum() if $type == $ALPHANUM;
        $arg = getTestPath() if $type == $PATH;

        # arg format is '/' argname ':' arg
        # examples: /n:test and /n:42
        $args = $args . " /" . $whicharg . ":$arg";
    }

    # Call the app with the args.
    `$exe $args`;
    $? >>= 8;

    printf "$exe returned $?\n";
}

# Handler functions

# Return a numeric test result; 
# 10% of the time, result is zero.
# Otherwise it's a value between -32000 and 32000.
sub getTestNumeric {
    return rand > .9 
 ? 0 
                : (int rand 32000) - (int rand 32000);
}

# Return a random length string. 
sub getTestAlphaNum {
    return 'A' x rand 32000;
}

# Return a path with multiple dirs, of multiple length.
sub getTestPath {
    my $path="c:\\";
    for (my $i = 0;  $i < rand 10; $i++) {
        my $seg = 'a' x rand 24;
        $path=$path . $seg . "\\";
    }

    return $path;
}
