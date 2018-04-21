# CryptographyProject-2
An Integrated Environment of a User-driven Automated Generation of Implementations of Cryptography Solutions

### Implementation

The project consists of a software implementation and demonstration of a graphical user interface (GUI) that facilitates a user with no (or a minimal amount of) cryptography knowledge to implement moderately complex cryptography solutions by writing no (or a minimal amount of) code. The GUI would allow the user to design a complex cryptographic protocol between 2 parties: Alice and Bob, by selecting, for each of the two parties, a sequence of dependent executions of cryptographic algorithms, primitives, or protocols (these can be any among symmetric/asymmetric encryption, message authentication schemes, digital signatures, key agreement protocols, one-way trapdoor permutations, etc.) as well as basic coding instructions (i.e., assignments between outputs/inputs of these algorithms) and basic messaging instructions (e.g., Alice sends a message to Bob, and viceversa). The set of algor#ithms, primitives, or protocols, and their syntax should be as specified in the lecture documents.

The project consists fo the following steps:

1. Choose your complex cryptographic protocol to demonstrate; generic suggestions include the following:
    - Alice encrypts a message to Bob using a hybrid encryption scheme
    - Alice encrypts a message to Bob using an encryption scheme that is IND-CCA-secure
    - Alice and Bob agree on a session key and then Alice encrypts a message to Bob using a symmetric encryption scheme based on the session key
    - Alice stores on and later retrieves hashed passwords from Bob
    - Alice stores on and later retrieves encrypted files from Bob
    - Alice and Bob use homomorphic encryption to securely compute a function of their private inputs
    - Your favorite cryptographic protocol
    
2. Implement all cryptographic primitives, basic coding instructions, and basic messaging instructions used by the specified protocol by suitable calls to open-source software libraries (e.g., OpenSSL, Crypto++, Miracl, etc.)

3. Implement the GUI that combines your implementation of cryptographic primitives, basic coding instructions, and basic messaging instructions into an implementation of your complex cryptographic protocol

4. Demonstrate that the GUI allows a user to produce an implementation of your complex cryptographic protocol

5. Prepare a project presentation file (using, for instance, Microsoft Powerpoint) including a detailed description of above steps 1-4, together with a demonstration (using videos or screenshots) of how your GUI works while taking commands from a user. You will give a 10/15-min oral presentation

### Submission Criteria
- Complex cryptographic solution choice (i.e., if you chose an interesting and complex enough cryptographic protocol, etc.)
- Specification validity (i.e., if you properly specified all steps for Alice and Bob to realize your complex cryptography protocol, etc.)
- GUI Design validity (i.e., if you chose appropriate cryptographic primitives, if the schemes implementing the primitives and their key length parameters are valid choices in terms of security and efficiency)
- GUI Implementation validity (i.e., if your software, after inspection of the presentation demonstration and some amount of testing, seems to satisfy correctness; if your software is easy to use / run, has a well-written readme file, etc.)
- Demonstration/presentation quality (i.e., if the presentation is well written and insightful, if the demonstration is clear and insightful, etc.)

### Presentation
In your presentation, you have to describe above project steps 1-4, together with a demonstration (using videos and/or screenshots) of how your solution works.  If this is a team effort, all students in the team have to about equally share the burden of the presentation (for instance, split the presentation into time slots and each team member presents during one of the slots). Remember that you have a total of 10-15 minutes for the video presentation of steps 1-4 + demonstration.
