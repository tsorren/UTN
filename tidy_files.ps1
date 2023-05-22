dir -Recurse | 
Where-Object { $_.name.Contains(" ") } |
Rename-Item -NewName { $_.name -replace " ","_" }

ls *.exe -Recurse | foreach {rm $_}