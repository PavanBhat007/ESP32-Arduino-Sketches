# https://api.thingspeak.com/channels/<channel_id>/fields/<field_id>.<format>

from email.mime.text import MIMEText 
from email.mime.image import MIMEImage 
from email.mime.application import MIMEApplication 
from email.mime.multipart import MIMEMultipart 
import smtplib 
import os 
 
smtp = smtplib.SMTP('smtp.gmail.com', 587) 
smtp.ehlo() 
smtp.starttls() 

smtp.login('Your Email', 'Your Password') 
def message(subject="Python Notification", 
			text="", img=None, attachment=None): 
	msg = MIMEMultipart() 
	msg['Subject'] = subject 
	msg.attach(MIMEText(text)) 

	if img is not None: 
		if type(img) is not list: 
			img = [img] 

		for one_img in img: 
			img_data = open(one_img, 'rb').read() 
			msg.attach(MIMEImage(img_data, 
								name=os.path.basename(one_img))) 

	
	if attachment is not None: 
		if type(attachment) is not list: 
			attachment = [attachment] 

		for one_attachment in attachment: 
			with open(one_attachment, 'rb') as f: 
				file = MIMEApplication( 
					f.read(), 
					name=os.path.basename(one_attachment) 
				) 
			file['Content-Disposition'] = f'attachment;\ 
			filename="{os.path.basename(one_attachment)}"' 
			msg.attach(file) 
	return msg 


msg = message("Good!", "Hi there!") 

to = ["ABC@gmail.com", 
	"XYZ@gmail.com", "insaaf@gmail.com"] 

smtp.sendmail(from_addr="hello@gmail.com", 
			to_addrs=to, msg=msg.as_string()) 

smtp.quit()
