Encryption on hardware is bit tricky, so for now this example shows how to encrypt a connection between two NodeJS apps. The only major difference between a regular TCP connection is the private Key, and the public certificate that you have to set in to an option object.

# How to Create a Key and Certificate

The first step in this security process is the creation of a private Key. What is this private Key I hear you ask? Basically it is a set of random noise used to encrypt things. In theory you could create one key and use it to encrypt what ever you want. But it is best practice to have different Keys for specific things. Because if someone steals your private key, it is the same as if they stole your house keys. Imagine if you used the same key to lock, your car, garage, office etc.

`openssl genrsa -out private-key.pem 1024`

Once we have our private key we can create a csr (certificate signing request), which is our request to get our private key signed by a fancy authority. That is why you have to input information related to your *company*. This information will be seen by the signing authority and used to verify you. In our case it doesn’t matter what you type, since in the next step we are going to sign our certificate ourselves.

`openssl req -new -key private-key.pem -out csr.pem`

Now that we have our *paper work* filled out, it is time to pretend we are a cool signing authority.

`openssl x509 -req -in csr.pem -signkey private-key.pem -out public-cert.pem`

Now that you have the private key and the public cert, you can establish a secure connection between two NodeJS apps. And as you can see in the example code. It is a very trivial process.

# Important

Since we created the public cert, in true honesty, our certificate is worthless, because we are nobodies. The NodeJS server won't trust such certificate by default, and that is why we need to tell it to actually trust our cert with the following option `rejectUnauthorized: false`. **Very important**: never set this variable to `true` in a production environment.

# Pro Tip

The csr.pem and public-cert.pem files are encoded in base64, witch means you can easily convert them back in to a string. Check them out and see what they are hiding :).
