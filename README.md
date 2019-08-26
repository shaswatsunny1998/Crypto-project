<img src="http://bsmedia.business-standard.com/_media/bs/img/article/2015-08/28/full/1440706704-1419.jpg" alt="Bank" style="margin-left:10px;"/>

<br><br>


# Bank Security Holder :bank:
Our project proposes a verified ATM (Automated Teller Machine) utilizing a card checking framework alongside an OTP password framework through SMS for improved security. Regular ATM systems don't contain the OTP feature for the withdrawing of cash. On the off chance that an assailant figures out how to get hold of ATM card and the pin number, he may effectively utilize it to pull back cash without our insight. Thus, our proposed idea underpins the ATM card scanning along with an OTP. As per this system, the client may examine his card and log in to the system with the separate OTP. After the client is through with this confirmation, he may see subtleties, similar to his bank equalization or exchange history, however, is approached to enter OTP when he clicks cash withdrawal option. At this stage, the framework creates and sends a One-time Password (OTP) to the enrolled mobile number of that specific client. This telephone number must be related to the client's bank account. He now needs to enter the OTP in the system so as to withdraw cash. Subsequently, our framework gives a thoroughly secure approach to perform ATM exchanges with two-level security structure. In the system structure, the Onetime Password which is sent to the client is encrypted when sent from the bank's database and only decrypted when received by the client. Henceforth that OTP can't be intercepted by anybody in between of the bank and the account holder.

## Introduction
Automatic Teller Machines (ATMs) are self-service banking machines that allow customers to access their bank account without the aid of a bank teller or bank clerk. They are used for financial transactions, they operate 24 hours a day helping customers to withdraw cash, deposit cash, transfer funds, check account balance, and print statement of account. They are placed in convenient locations such as the retail outlets, banking premises, grocery stores, shopping malls and gas stations. They make banking transaction easier, by helping banks to meet the demands of their customers; customers do not need to go to the banking hall or even in some cases they do not need to queue in banks just to make basic banking transactions. Some ATM machines allow customers of different banks to perform basic banking transactions without going to their bank or their banks ATM machine. Despite all these advantages, it has been reported in that customers and banks are faced with a lot of ATM fraud and other ATM security-related problems. Therefore, there is a need to provide a means of securing ATM transaction against frauds and crimes. This study presents how the Short Message Service (SMS) encrypted message can help make ATMs more secured. The proposed technology includes the use of existing Personal Identification Number (PIN) to provide authentication of the card to card issuer host system and the use of SMS encrypted message to authenticate customers before any transaction can take place at the ATM machine.


## Why Bank Security Holder?
With the growing number of ATM put in use, ATM security breaches are now a daily occurrence around the world. Attacks on ATM include phishing, shoulder surfing and the installation of ATM skimmer. ATM skimmers are used to read the ATM card number. Cameras are also installed at the ATM to read the PIN and other bank account information’s. This stolen information’s can be used to create fake or cloned ATM cards which can be used to steal money from the customer’s account. ATM PIN verification uses an encryption technique. Access to PINs of some cards issued from the same bank can help an attacker determine the encryption key used by that bank hence the PIN to any ATM card issued by that bank can then be determined. ATM fraudsters have become more sophisticated, they have used ATM machine to defraud banks. To address these issues, banks and customers are requiring new security enhancements for ATMs in order to provide improved security for financial institutions and prevent ATMs from being compromised.

## What is Elliptical Curve Cryptography?
Elliptical curve cryptography (ECC) is a public key encryption technique based on elliptic curve theory that can be used to create faster, smaller, and more efficient cryptographic keys. ECC generates keys through the properties of the elliptic curve equation instead of the traditional method of generation as the product of very large prime numbers. The technology can be used in conjunction with most public-key encryption methods, such as RSA, and Diffie-Hellman. According to some researchers, ECC can yield a level of security with a 164-bit key that other systems require a 1,024-bit key to achieve. Because ECC helps to establish equivalent security with lower computing power and battery resource usage, it is becoming widely used for mobile applications. ECC was developed by Certicom, a mobile e-business security provider, and was recently licensed by Hifn, a manufacturer of integrated circuitry (IC) and network security products. RSA has been developing its own version of ECC. Many manufacturers, including 3COM, Cylink, Motorola, Pitney Bowes, Siemens, TRW, and VeriFone have included support for ECC in their products.
More about the ECC can be found [here.](https://en.wikipedia.org/wiki/Elliptic-curve_cryptography)

## Architecture Design
After a thorough study of the security features in an ATM transaction, a security scheme is proposed. Our proposal is not replacing the existing security technology; rather it serves as an additional layer of security that protects the existing authentication system from frauds and crimes. Our concern is to provide a secure end to end communication of OTP to the customer by encrypting the SMS message used to send the OTP from the bank server to the customer’s mobile phone. There are two banking modules in the proposed secure model, one at the bank server and the other on customer’s mobile phone. The module at the bank server will contain a database where the entire customer’s encryption key will be stored. This encryption key will be used to encrypt the SMS message containing the generated OTP before it is sent to the customer’s mobile phone. The module on the customer’s mobile phone will contain the decryption key for decrypting received encrypted SMS from the bank server. This module is password-based; the customer needs to enter a password before access is granted to the module. This is done in order to secure the module from unauthorized users. Both modules use Elliptic curve encryption for encrypting and decrypting the SMS message containing the OTP. An elliptic curve is an asymmetric encryption technique. The study also explained that Elliptic curve encryption technique is a suitable asymmetric encryption technique for encrypting SMS transmitted message due to its ability to use smaller key size to obtain same security as compared to other asymmetric encryption techniques. Asymmetric encryption technique is used in the proposed model in order to prevent the decryption key from being compromised. On like the symmetric encryption technique which uses the same key for encryption and decryption, the Asymmetric encryption uses two related keys, public and private key. The public key will be stored in the bank server database while the private key will be stored in the customer’s mobile phone. If the database containing the customers encrypting key is compromised, the decryption key will definitely not be compromised since the decryption key is stored in the customer’s mobile phone. Using asymmetric encryption to encrypt the SMS message containing the OTP at the bank computer and decrypting it after it is received at the customer’s mobile phone will prevent the OTP against eavesdropping and interception, thereby providing security to ATM transactions. Customer’s public and private keys can be generated by physically connecting the customer’s mobile phone to the bank computer using a cable. The public key is stored in a database at the bank server as the encrypting key while the private key will be stored on the customer’s mobile phone as the decrypting key. These keys can only be renewed if the customer’s mobile phone is physically connected to the bank’s computer. In the proposed technology, if the customer initiates a transaction at the ATM, after entering the PIN, if the PIN is authenticated, the bank server generates the OTP, gets the customer’s public key from the database, encrypt the OTP and send it to the customer’s mobile phone via SMS. Customer on receiving the encrypted SMS decrypts it using the private key to get the OTP. This additional layer on the existing security technology will help protect the OTP’s transmission from malicious attack and eavesdropping, thereby providing security to ATM transactions.
<br><br>

<center> <h2> Project Architecture </h2> </center>

![Architecture](/images/ecc-1.JPG)

<hr>

<center> <h2> Server-Client Architecture </center>

![server-client](/images/ecc-2.JPG)



## Why Using Elliptical Curve Cryptography?
On comparing the length of the key of RSA and Elliptic Curve cryptography, we found the following data -

|Symmetric Key Size <br>(bits)|RSA and Diffie-Hellman Key Size<br>(bits)| Elliptic Curve Key Size<br>(bits) |
|-----|-----|-----|
|80|1024|160 |
| 112 |2048 |224 |
|128|3072|256 |
|192| 7680 |384 |
|256| 15360| 521|

This shows that to get similar security levels on both RSA and Elliptic Curve, the latter does its job much better and efficiently. The small key sizes make ECC very appealing for devices with limited storage or processing power, like our smartphones. The smaller space it takes to store the keys with the same level of security, much better.

## Files
- In this project we have created 3 C++ files namely - 
	1. [Server.cpp](https://github.com/shaswatsunny1998/Crypto-project/blob/master/Preserved/server.cpp)- This file contains all the ECC algorithm and generation of OTP. It also contains the source code of creating a TCP socket and binding it. It is responsible for sending the message buffer to the client. 
	2. [Client.cpp](https://github.com/shaswatsunny1998/Crypto-project/blob/master/Preserved/client.cpp)- This file contains all the ECC algorithm along with the listening socket for the client. When the sever is sending some message to the socket, the client is listening the socket and message buffer from the server and decode the message and show the output.
	3. [FiniteFieldElement.hpp](https://github.com/shaswatsunny1998/Crypto-project/blob/master/Preserved/FiniteFieldElement.hpp)- This file is the header file. Since Elliptical curve cryptography is a part of the finite field. So, all the operations that happened in the ECC are the abelian group operations of the Finite Field Element. All the element operations are defined in this file along with the utils function and point representation of the ECC point.



## Secure the Bank!
 

### How To Use
 > The application is compatible with Linux system **only**.
- #### Running the application-
	1. git clone https://github.com/shaswatsunny1998/Crypto-project.git
	2. cd Crypto-projcect-master
	3. cd Preserved
	4. Type   `./server`
	5.  Enter the **4 digit OTP.**
	6. Open another terminal.
	7. cd cd Crypto-projcect-master
	8. cd Preserved
	9. Type `./client`

 
- #### Compiling the files- 
	1. cd Preserved
	2. `g++ -o server server.cpp`
	3. `g++ -o client client.cpp`


## Conclusion
The main working of the system is that the bank will enter the OTP. It will encrypt the OTP using its private key and shared key between the bank and the user and using the ECC algorithm. After that it will create a socket and will send the encrypted message to the client i.e. the user. After that the user will read the message and decrypt the message using its private key and shared key between the bank and the user. After that for the authentication the user has to enter the OTP in the ATM. If he entered wrong OTP authentication is failed else authentication success. Also, if a eavesdropper is trying to get the encrypted message, he will expose himself and the bank will be alerted as the data is being accessed by the unauthorized person.
<hr>
