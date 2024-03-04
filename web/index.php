<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" href="http://www.web.com/styles.css">
    <title>table de multiplication</title>
</head>
<body>
    <?php
        $a=$_POST["a"];
        $b=$_POST["b"];
    
        session_start();
        $_SESSION["a"]=$a;
        $_SESSION["b"]=$b;
        $_SESSION["mult_table"]=createTable($a, $b);    
        

        $line=$_GET["ligne"];
        $action=$_GET["action"];
        
        if($action=="supprimer"){
            
            session_start();
            $_table=$_SESSION["mult_table"];
            $A=$_SESSION["a"];
            $B=$_SESSION["b"]-1;

            //array_splice($table, $line, 1);
            showTable($A, $B, $table);

            echo"<h1>miofjidfpkflsjkdfoa$line</h1>";

            $_SESSION["mult_table"]=$table;
            $_SESSION["b"]=$B;
        }
                

        else{
            //session_start();
            echo"<h1>multiplication</h1>";
            showTable($_SESSION["a"], $_SESSION["b"], $_SESSION["mult_table"]);
        }
        

        function showTable($a, $b, $tab){
            echo " <div class='table-mult'><table><tr style='background-color: rgb(145, 145, 204);'><td>a</td><td>b</td> <td>a * b</td><td class='champ-modify'>modification</td></tr>";            
            for($i=1;$i<=$b;$i++){
                echo "<tr style='background-color:" .$tab[$i][3]. ";'>
                        <td>" .$tab[$i][0]. "</td><td>" .$tab[$i][1]. "</td><td>" .$tab[$i][2]. "</td>
                        <td class='champ-modify'>
                            <a href='index.php?action=supprimer&ligne=$i' class='mod-button'>supprimer</a>
                            <a href=?action=modifier&ligne=$i class='mod-button'>modifier</a>
                        </td>
                    </tr>"; 
            }
            echo"</table></div>";  
        }

        function createTable($a, $b){
            $tab=array();
            for($i=1;$i<=$b;$i++){
                $somme=$a*$i;
                $tab[$i][0]=$a;
                $tab[$i][1]=$i;
                $tab[$i][2]=$somme;
                if($i%2==0){
                    $tab[$i][3]="grey";
                }
                else $tab[$i][3]="rgb(173, 171, 171)";
            }
            return $tab;
        }
    ?>

</body>
</html>
