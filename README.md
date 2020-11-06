# ArduinoOSEK_EE
This repo contains 2 files that must be imported into an Eclipse RT-Druid project.
# Preliminary steps to be performed:
--linux environment setup
  # 1:
      install arduino sdk (second way is raccomandend!!)
        # first way: sudo apt-get install arduino
        # second way: download and install sdk from: https://www.arduino.cc/en/software
        # remeber the dir whenever y put and installed the sdk!! (dpkg -L arduino)
  # 2:
      install java sdk and java runtime env. for Eclipse:
        # check if installed with: java -version
        # if not:  sudo apt-get install default-jre
                   sudo apt-get install default-jdk
  # 3:
      install git:
      # sudo apt-get install git
  # 4:
      install cmake,python,flex,bison
      # sudo apt-get install python
      # sudo apt-get install flex
      # sudo apt-get install bison
      # sudo apt-get install doxygen
  # 5:
      install arm-gnu toolchain
      # sudo apt-get install gcc-arm-none-eabi
  # 6:
      install avr-gcc arduino cross compiler
      # sudo apt-get install avr-libc gcc-avr avrdude
  # 7: 
      doxygen:
      # git repo clone: git clone https://github.com/doxygen/doxygen.git
      # cd doxygen
      # mkdir build
      # cmake -G "Unix Makefiles" ..
      # sudo make
      # sudo make install
  # 8:
      connect arduino via USB and be shure that is connected to serial port ttyACM0 (Ubuntu):
      # check where arduino is connected: dmesg
      # only root or group 'dialout' can access /dev/ttyACM0 serial port so: 
      # sudo adduser $USER dialout
      # check if y are part of 'dialout': groups $USER
      # check if y can write or read from /dev/ttyACM0: cat /dev/ttyACM0, echo "hello world" > /dev/ttyACM0
      # if not: sudo chmod a+rw /dev/ttyACM0
      
 # Download Erika Enterprise v3.x: 
      (y'll be asked to accept a license)-> http://www.erika-enterprise.com/index.php/download/erika-v3-download.html 
     
 # Eclipse RT-Druid configuration:
      (follow official EE guideline in pdf file)
      
 # Additional Tools May be useful:
      # Putty: sudo apt-get install putty
 
    
        
                      
