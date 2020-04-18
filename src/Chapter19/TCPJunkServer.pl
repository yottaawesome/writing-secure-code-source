# TCPJunkServer.pl

use IO::Socket;

my $port = 80;
my $server = IO::Socket::INET->new(LocalPort => $port,
                                   Type => SOCK_STREAM,
                                   Reuse => 1,
                                   Listen => 100)
    or die "Unable to open port $port: $@\n";

while ($client = $server->accept()) {
   
    my $peerip = $client->peerhost();
    my $peerport = $client->peerport();

    my $size = int rand 16384;
    my @chars = ('A'..'Z', 'a'..'z', 0..9, qw( ! @ # $ % ^ & * - + = ));
    my $junk = join ("", @chars[ map{rand @chars } (1 .. $size)]);

    print "Connection from $peerip:$peerport, ";
 print "sending $size bytes of junk.\n";
   
    $client->send($junk);
}

close($server);
