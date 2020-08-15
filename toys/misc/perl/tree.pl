use Tree::Visualize;
use Tree::Binary;
use Tree::Binary::Search;
  
  my $tree = Tree::Binary->new("*")
                          ->setLeft(
                              Tree::Binary->new("+")
                                          ->setLeft(Tree::Binary->new("2"))
                                          ->setRight(Tree::Binary->new("2"))
                          )
                          ->setRight(
                              Tree::Binary->new("+")
                                          ->setLeft(Tree::Binary->new("4"))
                                          ->setRight(Tree::Binary->new("5"))
                          ); 
  
  my $visualize = Tree::Visualize->new($tree, 'ASCII', 'TopDown');
  print $visualize->draw();   
  
  #                 +---+                 
  #        +--------| * |-------+         
  #        |        +---+       |         
  #      +---+                +---+       
  #   +--| + |--+          +--| + |--+    
  #   |  +---+  |          |  +---+  |    
  # +---+     +---+      +---+     +---+  
  # | 2 |     | 2 |      | 4 |     | 5 |  
  # +---+     +---+      +---+     +---+  

  my $tree = Tree::Binary::Search->new();
  foreach my $value (7, 3, 1, 0, 2, 5, 4, 6, 11, 9, 10, 8, 13, 12, 14) {
    $tree->insert($value => $value);
  }
  exit;
  
  my $visualize = Tree::Visualize->new($tree, 'ASCII', 'Diagonal');
  print $visualize->draw(); 

  # (7)-------------(11)-----(13)-(14)
  #  |                |        |      
  #  |                |      (12)     
  #  |                |               
  #  |              (9)-(10)          
  #  |               |                
  #  |              (8)               
  #  |                                
  # (3)-----(5)-(6)                   
  #  |       |                        
  #  |      (4)                       
  #  |                                
  # (1)-(2)                           
  #  |                                
  # (0)
  
  my $tree = Tree::Simple->new("test")
                        ->addChildren(
                            Tree::Simple->new("test-1")
                                ->addChildren(
                                    Tree::Simple->new("test-1-1")
                                    ),
                            Tree::Simple->new("test-2"),
                            Tree::Simple->new("test-3")
                            );  
                            
  my $visualize = Tree::Visualize->new($tree, 'ASCII', 'TopDown');
  print $visualize->draw();   
  
  #                   |                  
  #               +------+               
  #               | test |               
  #               +------+               
  #       ____________|_____________     
  #       |            |           |     
  #  +--------+   +--------+  +--------+ 
  #  | test-1 |   | test-2 |  | test-3 | 
  #  +--------+   +--------+  +--------+ 
  #       |                              
  #       |                              
  # +----------+                         
  # | test-1-1 |                         
  # +----------+              
  
