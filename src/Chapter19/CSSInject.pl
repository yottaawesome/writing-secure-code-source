# CSSInject.pl
use HTTP::Request::Common qw(POST GET);
use LWP::UserAgent;

# Set the user agent string.
my $ua = LWP::UserAgent->new();
$ua->agent("CSSInject/v1.36 WindowsXP"); 

# Various injection strings
my @css = ('><script>alert(window.location);</script>',
           '\"; alert(document.cookie);',
           '\' onmouseover=\'alert(document.cookie);\' \'',
           '\"><script>alert(document.cookie);</script>',
           '\"></a><script>alert(document.cookie);</script>');

# Build the request.
my $url = "http://127.0.0.1/form.asp";
my $inject;
foreach $inject (@css) {
   
    my $req = POST $url, [Name => $inject, 
                          Address => $inject, 
                          Zip => $inject];
    my $res = $ua->request($req);

    # Get the response.
    # If we see the injected script, we may have a problem.
    $_ = $res->as_string;    
    if (index(lc $_, lc $inject) != -1) {
        print "HHMM! Possible CSS issue in $url\n" ;
    }
}
