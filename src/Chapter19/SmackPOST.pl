# SmackPOST.pl
use HTTP::Request::Common qw(POST GET);
use LWP::UserAgent;

# Set the user agent string.
my $ua = LWP::UserAgent->new();
$ua->agent("HackZilla/v42.42 WindowsXP"); 

# Build the request.
my $url = "http://127.0.0.1/form.asp";
my $req = POST $url, [Name => 'A' x 128, 
           Address => 'B' x 256, 
           Zip => 'C' x 128];
$req->push_header("Timestamp:" => '1' x 10);
my $res = $ua->request($req);

# Get the response.
# $err is the HTTP error and $_ holds the HTTP response data.
my $err = $res->status_line;    
$_ = $res->as_string;    
print " Error!" if (/Illegal Operation/ig || $err != 200);
