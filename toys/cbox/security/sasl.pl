#!/usr/bin/env perl

use Crypt::OpenSSL::AES;

$key = "nowisthetimeforallgoodmentocomet";
my $cipher = new Crypt::OpenSSL::AES($key);

$plaintext = "so wudup dawg un";
print "plain: $plaintext\n";

$encrypted = $cipher->encrypt($plaintext);
print "encr: `$encrypted`\n";

$decrypted = $cipher->decrypt($encrypted);
print "decr:  $decrypted\n";


