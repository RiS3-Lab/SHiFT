## GDBFuzz
### Switching to AFL++ standalone mutator
- Consider GDBFuzz is set up properly
- Go to `gdbfuzz/dependencies/AFLplusplus/custom_mutators/aflpp/standalone`
- `make`
- open `gdbfuzz/src/GDBFuzz/fuzz_wrappers/InputGeneration.py`
- replace the function `generate_input` with the follow:
> 
    def generate_input(self) -> bytes:
        
        # After a reset, we first try all corpus files again
        if self.retry_corpus_input_index < len(self.corpus):
            input = self.corpus[self.retry_corpus_input_index].content
            self.retry_corpus_input_index += 1
            return input
        stand_alone_dir = '/home/lcm/github/shift/gdbfuzz/dependencies/AFLplusplus/custom_mutators/aflpp/standalone'
        aflpp_standalone_mutator = os.path.join(stand_alone_dir,'aflpp-standalone')
        aflpp_input_file = os.path.join(stand_alone_dir,'input.bin')
        aflpp_output_file = os.path.join(stand_alone_dir,'output.bin')
        with open(aflpp_input_file,'wb') as f:
            f.write(self.corpus[self.current_base_input_index].content)
        p = subprocess.call([aflpp_standalone_mutator,aflpp_input_file,aflpp_output_file])
        retry_num = 0
        while p != 0:
            p = subprocess.call([aflpp_standalone_mutator,aflpp_input_file,aflpp_output_file])
            retry_num += 1
            if retry_num >= 7:
                print("AFL++ mutator failed for {} times".format(retry_num))
        with open(aflpp_output_file,'rb') as f:
            generated_inp = f.read()
        
        #generated_inp = _pylibfuzzer.mutate(self.corpus[self.current_base_input_index].content)
        return generated_inp
- Adjust your `stand_alone_dir` accordingly in your code. 