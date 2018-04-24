#include <botan/auto_rng.h>
#include <botan/rsa.h>
#include <botan/pubkey.h>
#include <botan/hex.h>
#include <iostream>

void RSASig() {
	Botan::AutoSeeded_RNG rng;

	
	Botan::RSA_PrivateKey key(rng, 2048);
	std::cout << "Key generated!\n";

	Botan::RSA_PublicKey pub(key.get_n(), key.get_e());

	std::vector<uint8_t> pubser = pub.public_key_bits();
	std::cout << "Signature:" << std::endl << Botan::hex_encode(pubser) << std::endl;


	std::string text("");
	std::vector<uint8_t> data(text.data(),text.data()+text.length());



	Botan::PK_Signer signer(key, rng, "EMSA1(SHA-256)");

	// sign data
	signer.update(data);
	std::vector<uint8_t> signature = signer.signature(rng);
	std::cout << "Signature:" << std::endl << Botan::hex_encode(signature);

	// Decipher



	// verify signature
	Botan::PK_Verifier verifier(key, "EMSA1(SHA-256)");
	verifier.update(data);
	std::cout << std::endl << "is " << (verifier.check_signature(signature)? "valid" : "invalid");
}


int main() {

	RSASig();
	return 0;
}
