# This code opens a TCP socket to 
# a server listening on port 1777;
# sets a query action; 
# sends MAX_BLOB letter ‘A’s to the port.
use IO::Socket;
my $MAX_BLOB = 128;
my $actAction = 0;   # ACTION_QUERY
my $bBlob = 'A' x $MAX_BLOB;
my $cbBlobSize = 128;   
my $server = '127.0.0.1';
my $port = 1777;

if ($socks = IO::Socket::INET->new(Proto=>"tcp",
                                    PeerAddr=>$server,
                                    PeerPort => $port,
                                    TimeOut => 5)) {
    my $junk = pack "ssa128",$actAction,$cbBlobSize,$bBlob;
    printf "Sending junk to $port (%d bytes)", length $junk;
    $socks->send($junk);
}
