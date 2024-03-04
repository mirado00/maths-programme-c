<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
</head>
<body>
    <?php
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

        //  showTable($_SESSION["a"],$_SESSION["b"] , $_SESSION["mutl_table"]);


    ?>
</body>
</html>