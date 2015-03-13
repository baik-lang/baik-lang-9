$dir = ".";

opendir DIR, $dir;
@files = grep { !m/^(\.|\.\.)$/g } readdir DIR; 
close DIR;

$flag = @files;

if ( $flag ) { 
   foreach $file ( @files ) {
     #print $file . "\n";
     &read_file($file);
   }
}

end;


sub read_file {
  $filename = $_[0];

  open(FIN, $filename);

  while($line=<FIN>) {
    if($line =~ m/seluruh_arsip/i) {
      print "$filename $line";
    }

  }

  close(FIN);
}

