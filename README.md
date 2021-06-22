# Software for managing the technological process of conducting communication sessions
# ПО управления ходом технологического процесса проведения сеансов связи

Client
Server
resource - The folder contains instructions for the Server operation and commands to be executed by the Client.

* **resource/Server/rules.json** - The file contains the process roles and the socket descriptor of this role

```json
{
    "Наблюдатель 1" : 0,
    "Observer 2" : 0
}
```

* **resource/Server/timer_do.json** - The file contains the execution time, and a link to the file, 
which has its own instructions attached to each role.

```json
{
    "19.06.2021 08:20:20" : "/home/{}/Desktop/transmit/resource/Server/rules_files.json"
}
```

* **resource/Server/rules_files.json** - The file contains all the roles and the path to each instruction executed by the client.

```json
[
	    {"Наблюдатель 1": "/home/{}/Desktop/transmit/resource/Client/inst1/instructions1.json"} ,
      {"Observer 2": "/path/instructions2.json"}
]
```

* **resource/Client/inst1/inst*1.json** - The file contains the instructions that the client must execute.

```json
{
	"COMMANDS": [
		{"SEND_FILE": {
			"PATH_CLIENT": "/home/{}/Desktop/transmit/resource/Client/demo.mp4",
			"PATH_SERV": "/home/{}/Desktop/transmit/resource/demka20.mp4"
			}
		},
		{"COMPLITE_SOFT": "/home/{}/Downloads/LinuxOfflineInstaller.run"},
		{"GET_FILE": {
			"PATH_SERV": "/home/{}/Desktop/transmit/resource/demka.mp4",
			"PATH_CLIENT": "/home/{}/Desktop/transmit/resource/Client/demka20.mp4"
			}
		},
		{"COPY_FILE": {
			"FROM": "/home/{}/Desktop/transmit/resource/Client/removeFile.cpp",
			"TO": "/home/{}/Desktop/transmit/resource/Client/removeFile2.cpp"
			}
		},
		{"REMOVE_FILE": "/home/{}/Desktop/transmit/resource/Client/removeFile.cpp"}
	]
}
```
