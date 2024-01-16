use std::{fs, vec};

fn parse_input(content: &str) -> u32 {
    let num_vec:Vec<&str> = vec!["one", "two", "three", "four", "five", "six", "seven", "eight", "nine"];
    let res_vec:Vec<u32> = content.chars().enumerate().filter_map(|(idx,char)| match char {
        '1'..='9' => {char.to_digit(10)}
        _ => {
            num_vec.iter().enumerate().filter_map(|(jdx,&x)| match content.get(idx..idx+x.len()) {
                Some(s) if (s==x) => Some((jdx+1) as u32),
                _ => None
            }).next()
        }
    }).collect();
    let result = res_vec[0]*10+res_vec.last().unwrap();
    return result;
}

fn main() {
    let start = std::time::Instant::now();
    let contents = fs::read_to_string("../input.txt")
        .expect("Something went wrong reading the file");
    
    let result:u32 = contents.lines().map(|line| parse_input(line)).sum();
    let duration = start.elapsed();
    println!("{:?}, duration: {:?}", result, duration);
}
