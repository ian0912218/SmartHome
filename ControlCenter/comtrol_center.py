import smtplib

from email.mime.multipart import MIMEMultipart

from email.mime.text import MIMEText

import serial

import time

def sendEmailAlert(msg):

with smtplib.SMTP(host="smtp.gmail.com", port="587") as smtp:

content = MIMEMultipart()

content["subject"] = "[警報]"+msg

content["from"] = "nlt120@email.nlhs.tyc.edu.tw"

content["to"] = "nlt120@email.nlhs.tyc.edu.tw"

content.attach(MIMEText(msg))

try:

smtp.ehlo()

smtp.starttls()

smtp.login("你的gmail帳號", "你的應用程式密碼")

smtp.send_message(content)

print("訊息已發送!")

except Exception as e:

print("Error message: ", e)