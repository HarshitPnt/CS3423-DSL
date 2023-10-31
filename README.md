# CS3423-DSL
YAFSM is a Domain-Specific Language (DSL) designed to work with Finite State Machines (FSMs), specifically focusing on Deterministic Finite Automata(DFAs),Non-deterministic Finite Automata (NFA) and Pushdown Automata (PDA). 

With YAFSM, you can easily define, specify, and manipulate the behavior of these automata in a clear and concise manner.

## Documentation

The documentation for the project can be found [here](./docs/group-6-specification.pdf)

The slides for the project can be found [here](https://docs.google.com/presentation/d/1BU0YLWs0I-gMG1dZB3picEcueNStOehfVuSABhHd2-8/edit?usp=sharing)

The link for the drive with videos explaining the project can be found [here](https://drive.google.com/drive/folders/1eDh5Q3hlLjKLKKadjpGaRpsJAHpO_KMG?usp=drive_link)

## Contributors

- Vishal Devadiga - CS21BTECH11061
- Harshit Pant - CS21BTECH11021
- Satpute Aniket Tukaram - CS21BTECH11056
- Mahin Bansal - CS21BTECH11034

## Running the code

Make sure you have the following installed on your system:
```
make, lex, bison, gcc, g++
```

To run the code, follow these steps:
```bash
cd ./parser
make run FILEPATH
```
where FILEPATH is the path of the code to be compiled.

### Testing

To test a specific component(Eg: lexer, parser, etc), run the following command(s):
```bash
cd ./scripts
./test.sh <component>
```

To test all components, run the following command:
```bash
cd ./scripts
./test.sh all
```
