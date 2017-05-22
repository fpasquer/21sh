<?php
    define ("SEEK",    "fcapocci");
    define ("REPLACE", "fpasquer");

    function parce_dir(string $path, $argv)
    {
        echo $path."\n";
        $list = scandir($path);
        foreach ($list as $v)
            if ($v != "." && $v != ".." && $v[0] != "." && $v != $argv)
            {
                if (is_dir($path."/".$v))
                    parce_dir($path."/".$v, $argv);
                else
                {
                    $file = file_get_contents($path."/".$v);
                    $new_content = str_replace(SEEK, REPLACE, $file);
                    $tmp = fopen($path."/".$v, "w+");
                    fprintf($tmp, "%s", $new_content);
                    fclose($tmp);
                    echo "\t".$path."/".$v."\n";
                }
            }
    }

    parce_dir(__DIR__, str_replace("./", "", $argv[0]));
?>