# Water_Quality_Prediction_System_using_IOT_and_AI

This is a hybrid system involving IOT and AI to predict water quality and suggest various water treatment processes. The project is divided into the following parts:

- Electronics
- IOT
- Cloud
- AI
- Python

## Overview

Sensors gather information about the water sample, MCU records the information, and pushes the data to a real-time database in the cloud. Various use cases with their thresholds are stored in a database in the cloud. Using Python, we extract the data as a JSON file and feed it into an LSTM model using a specifically engineered prompt. The AI gives the final output.

Each method is connected such that data moves seamlessly throughout the system. Each section is placed in different folders with files and codes. Read the README file carefully to understand the entire dynamics of the project.

## Future Controbutions

- Electronics - More advanced sensors can be introduced to the system
- Database - Efficient DBMS and constant update of new uses with corresponing thresholds
- AI - Newer fine tuned models
- Web Application - This part is totally empty, we need to work here.
