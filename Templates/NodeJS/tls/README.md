Encryption on hardware is bit tricky, so for now, this example shows how to encrypt a connection between two NodeJS apps. The only major differences between this and a regular TCP connection are the private Key and the public certificate that you’ll have to set into an option object.

# How to Create a Key and Certificate

The first step in this security process is the creation of a private Key. And what is this private key? Basically, it's a set of random noise that's used to encrypt information. In theory, you could create one key, and use it to encrypt whatever you want. But it is best practice to have different keys for specific things. Because if someone steals your private key, it's similar to having someone steal your house keys. Imagine if you used the same key to lock your car, garage, office, etc.

`openssl genrsa -out private-key.pem 1024`

Once we have our private key, we can create a CSR (certificate signing request), which is our request to have the private key signed by a fancy authority. That is why you have to input information related to your company. This information will be seen by the signing authority, and used to verify you. In our case, it doesn’t matter what you type, since in the next step we're going to sign our certificate ourselves.

`openssl req -new -key private-key.pem -out csr.pem`

Now that we have our paper work filled out, it's time to pretend that we're a cool signing authority.

`openssl x509 -req -in csr.pem -signkey private-key.pem -out public-cert.pem`

Now that you have the private key and the public cert, you can establish a secure connection between two NodeJS apps. And, as you can see in the example code, it is a very simple process.

# Important!

Since we created the public cert ourselves, in all honesty, our certificate is worthless, because we are nobodies. The NodeJS server won't trust such a certificate by default, and that is why we need to tell it to actually trust our cert with the following option rejectUnauthorized: false. **Very important**: never set this variable to true in a production environment.

# Pro Tip

The csr.pem and public-cert.pem files are encoded in base64, which means you can easily convert them back into a string. Check them out and see what they're hiding. :)
