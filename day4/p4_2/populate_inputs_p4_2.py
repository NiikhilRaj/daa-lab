import os
import random
import re

# Directory containing the input files
dir_path = os.path.dirname(os.path.abspath(__file__))

# Patterns to match file types and sizes
patterns = [
    (r'inAsce_(\d+)\.dat', 'asc'),
    (r'inDesc_(\d+)\.dat', 'desc'),
    (r'inRand_(\d+)\.dat', 'rand'),
    (r'inAsce\.dat', 'asc'),
    (r'inDesc\.dat', 'desc'),
    (r'inRand\.dat', 'rand'),
]

def get_size(filename):
    match = re.search(r'_(\d+)\.dat', filename)
    if match:
        return int(match.group(1))
    return 100  # Default size if not specified

def generate_sequence(seq_type, size):
    if seq_type == 'asc':
        return list(range(1, size + 1))
    elif seq_type == 'desc':
        return list(range(size, 0, -1))
    elif seq_type == 'rand':
        seq = list(range(1, size + 1))
        random.shuffle(seq)
        return seq
    else:
        raise ValueError('Unknown sequence type')

def main():
    files = os.listdir(dir_path)
    for fname in files:
        for pattern, seq_type in patterns:
            if re.fullmatch(pattern, fname):
                size = get_size(fname)
                seq = generate_sequence(seq_type, size)
                with open(os.path.join(dir_path, fname), 'w') as f:
                    f.write('\n'.join(map(str, seq)))
                print(f'Populated {fname} with {seq_type} sequence of size {size}')
                break

if __name__ == '__main__':
    main()
