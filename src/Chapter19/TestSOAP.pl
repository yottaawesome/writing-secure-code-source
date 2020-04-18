# TestSoap.pl
use HTTP::Request::Common qw(POST);

use LWP::UserAgent;                  
my $ua = LWP::UserAgent->new();
$ua->agent("SOAPWhack/1.0"); 

my $url = 'http://localhost/MySOAPHandler.dll';
my $iterations = 10;

# Used by coinToss
my $HEADS = 0;
my $TAILS = 1;

open LOGFILE, ">>SOAPWhack.log" or die $!;

# Some SOAP actions - add your own, and junk too!
my @soapActions=('','junk','foo.sdl');

for (my $i = 1; $i <= $iterations; $i++) {
    print "SOAPWhack: $i of $iterations\r";

    # Choose a random action.
    my $soapAction = $soapActions[int rand scalar @soapActions];
    $soapAction = 'S' x int rand 256 if $soapAction eq 'junk';
   
    my $soapNamespace = "http://schemas.xmlsoap.org/soap/envelope/";
    my $schemaInstance = "http://www.w3.org/2001/XMLSchema-instance";
    my $xsd = "http://www.w3.org/XMLSchema"; 
    my $soapEncoding = "http://schemas.xmlsoap.org/soap/encoding/";

    my $spaces = coinToss() == $HEADS ? ' ' : ' ' x int rand 16384;
    my $crlf = coinToss() == $HEADS ? '\n' : '\n' x int rand 256;

    # Make a SOAP request.
    my $soapRequest = POST $url;
    $soapRequest->push_header("SOAPAction" => $soapAction);
    $soapRequest->content_type('text/xml');
    $soapRequest->content("<soap:Envelope " . $spaces .
               " xmlns:soap=\"" . $soapNamespace . 
               "\" xmlns:xsi=\"" . $schemaInstance . 
               "\" xmlns:xsd=\"" . $xsd . 
               "\" xmlns:soapenc=\"" . $soapEncoding . 
               "\"><soap:Body>" . $crlf . 
               "</soap:Body></soap:Envelope>");

    # Perform the request.
    my $soapResponse = $ua->request($soapRequest);

    # Log the results.
    print LOGFILE "[SOAP Request]";
    print LOGFILE $soapRequest->as_string . "\n";

    print LOGFILE "[WSDL response]";
    print LOGFILE $soapResponse->status_line . " ";
    print LOGFILE $soapResponse->as_string . "\n";
            
} 

close LOGFILE;

sub coinToss {
    return rand 10 > 5 ? $HEADS : $TAILS;
}
