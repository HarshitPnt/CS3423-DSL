# Go to root directory
cd ../

# Generate specifications
cd ./docs/specs
pandoc --to latex specification.md --highlight-style zenburn -o ./pdf/group-6-specification.pdf
cd ../../

# Generate Project Log
cd ./docs/project_logs
rm -rf ./pdf
mkdir ./pdf
pdflatex project_log.tex
rm project_log.aux project_log.log project_log.out
mv project_log.pdf ./pdf/group-6-project-log.pdf
