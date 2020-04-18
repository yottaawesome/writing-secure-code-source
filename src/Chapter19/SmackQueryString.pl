# SmackQueryString.pl

use LWP::UserAgent;

$bogushdr = ('H' x 256) . '\n\r';
$hdr = new HTTP::Headers(Accept => 'text/plain',
                         User-Agent => 'HackZilla/42.42',
                         Test-Header => $bogushdr x 128);
                                                  
$urlbase = 'http://localhost/test.dll?data=';
$data = 'A' x 16_384;
$url = new URI::URL($urlbase . $data);
$req = new HTTP::Request(GET, $url, $hdr);

$ua = new LWP::UserAgent;
$resp = $ua->request($req);
if ($resp->is_success) {
    print $resp->content;
}
else {
    print $resp->message;
}
