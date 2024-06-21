"""
rsa_script.py - Decrypt some data using RSA

Usage: run "python rsa_script.py" and follow the prompts.

Project: Decryption with Python

Author: Imdad Ahad
Website: https://imdad.codes
Instagram: https://www.instagram.com/imdadcodes
TikTok: https://www.tiktok.com/@imdadahad
"""
import rsa
def load_private_key(private_key_location):
	private_key=None
	with open(private_key_location,"rb") as file:
		private_key=rsa.PrivateKey.load_pkcs1(
			file.read(),format='PEM'
		)
		return private_key

def rsa_decrypt(encrypted_data,private_key):
	decrypted=rsa.decrypt(encrypted_data,private_key).decode('utf-8')
	return decrypted

def run():
	private_key_location=input()
	private_key=load_private_key(private_key_location)
	encrypted_file_location=input("Enter the location")
	with open(encrypted_file_location,"rb") as file:
		encrypted_data=file.read()
		decrypted_data=rsa_decrypt(
			encrypted_data,private_key
		)
		print(f"The decrypted message is: {decrypted_data}")
if __namw__=='__main__':
	run()
