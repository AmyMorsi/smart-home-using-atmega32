# Smart-Garage-System

This project serves as an integral part of the ITI Embedded System diploma graduation project, which revolves around the development of a comprehensive Smart Home System.

Within this expansive endeavor, the Smart Garage Control System has been meticulously crafted to provide an advanced level of security and automation specifically tailored for garages.


Key Features:
   -   Password-Based Access: Users can enter a predefined password to open and close the garage door. The system checks the entered password for security.
      
   -   User Interface: The system employs a Character LCD (CLCD) for user interaction. It displays welcome messages, notifications, and status updates.
     
   -   Gate Control: The core functionality of the system is gate control. It can open and close the garage gate smoothly and securely.
     
   -   Safety: An Infrared (IR) sensor ensures safety by detecting obstacles or objects in the garage entrance. 
              If an obstruction is detected, the system halts the gate operation and alerts the user.
     
   -   Error Handling: The system provides error messages when an incorrect password is entered, guiding the user to retry. 
              It also alerts the user if the gate cannot close due to obstacles.

How It Works:
   - Users approach the garage and input their password using the keypad or another input method.
       
   - The system verifies the entered password for correctness.
       
   - If the password is correct, the system initiates the gate opening process.

   - An Infrared (IR) sensor constantly monitors the garage entrance for obstacles. 

   - If an obstacle is detected during gate closure, the system halts the gate operation and displays an alert message.

   - The system includes a timer mechanism to automatically close the garage gate after a set waiting period, enhancing security.
      
Customization:
   - The project is open-source and can be customized to suit specific needs and preferences. 

   - You can modify the password, timing, and sensor settings to align with your requirements.

Usage:
       This Smart Garage Control System is suitable for residential and commercial garages, providing enhanced security and convenience. 
       It can be integrated into existing home automation systems for a more comprehensive smart home experience.
