# Ft_transcendence
<a name="readme-top"></a>

<!-- TABLE OF CONTENTS -->
<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About The Project</a>
      <ul>
        <li><a href="#built-with">Built With</a></li>
      </ul>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
      </ul>
    </li>
    <li><a href="#Execution">Execution</a></li>
    <li><a href="#Annex">Annex</a></li>
  </ol>
</details>



<!-- ABOUT THE PROJECT -->
## About The Project

This is a C / C++ project. The aim is to change a string in the memory of another process while it's running.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

### Built With

<img src="https://img.shields.io/badge/-C-blue?logo=c">
<img src="https://img.shields.io/badge/-C++-blue?logo=cplusplus">

<p align="right">(<a href="#readme-top">back to top</a>)</p>



<!-- GETTING STARTED -->
## Getting Started
### Prerequisites

* Being on linux
* Having sudo privileges

## Execution

* First we have to find which pid the program is so we launch make proc, listing  new proc that last more than 30 seconds
![Proc](screenshots/makeproc.png)
* Than we execute our program and after 30 seconds we ca see some process starting
![Test](screenshots/maketest.png)
* To know which process is the one we are looking for, we look for the one with the string "bonjour" in its memory
![List](screenshots/makelist.png)
* After findig it (81929), we can change the string "bonjour" to another one with :
![Change](screenshots/makechange.png)
In the case we have a string like "bonjourbonjour" and we want to replace each "bonjour" by "hellocc" we'll put NBCHANGES=2
* Then we can see the change done to the memory
![Witness](screenshots/witnesschange.png)
* If you want to remove all the binary files
![Remove](screenshots/makerm.png)
## Annex

If the string is too short like "b" you'll probably face some problem like finding alot of b's in the memory.
We just keep process that last longer than 30 second to decrease the amount of temporary process in proc output.
If it's too long for you, you can adjust this time by modifying PROCCESS_TIME.

<p align="right">(<a href="#readme-top">back to top</a>)</p>
