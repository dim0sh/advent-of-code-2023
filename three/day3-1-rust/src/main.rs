use std::{collections::HashSet, fs, hash, vec};
#[derive(Debug, PartialEq, Eq, Hash, Clone)]
enum Element {
    Number(u32),
    Empty,
    Symbol,
}
fn find_symbol(input: &Vec<Element>) -> Vec<usize> {
    input.iter().enumerate().filter(|(_, e)| **e == Element::Symbol).map(|(i, _)| i).collect()
}
/*
 * find numbers around the symbol
 * Vec<Vec<uisze>> Beispiel: [[12,13,14],[2,3],[65,66]]
 * speichert die Indizes der Zahlen um das Symbol herum
 * wenn index um den index des symbols in Vec<Vec<uisze>> enthalten ist, dann return zahl.
*/
fn find_numbers(input: &Vec<Element>) -> Vec<Vec<usize>> {
    let mut num_vec = Vec::new();
    for (i,e) in input.iter().enumerate() {
        match e {
            Element::Number(_) => num_vec.push(i),
            _ => {},
        }
    }
    let mut result: Vec<Vec<usize>> = Vec::new();
    let mut temp: Vec<usize> = Vec::new();
    let mut i = 0;
    while i < num_vec.len() {
        
        if i == 0 {
            temp.push(num_vec[i]);
        } else if num_vec[i] == num_vec[i-1]+1 {
            temp.push(num_vec[i]);
        } else {
            result.push(temp);
            temp = Vec::new();
            temp.push(num_vec[i]);
        }
        i+=1;
    }
    result.push(temp);
    result
}
fn get_num(input: &Vec<Element>, index: &Vec<usize>) -> u32 {
    let mut result = 0;
    let mut i = index.len();
    for num in index.iter() {
        match input[*num] {
            Element::Number(n) => {result += n * 10u32.pow((i+1) as u32) },
            _ => {},
        }
        i-=1;
    }
    result/100
}
fn calc_surrounding_sum(input: Vec<Element>,width: i32) -> u32 {
    let surrounding_tiles: Vec<i32> = vec![
        -1, // left
        -1-width as i32, // left up
        -width as i32, // up
        -width as i32 + 1, // right up
        1, // right
        width as i32 + 1, // right down
        width as i32, // down
        width as i32 - 1, // left down
    ];
    let symbols = find_symbol(&input);
    let numbers = find_numbers(&input);
    let mut surr_index: Vec<usize> = Vec::new();
    for s in symbols.iter() {
        for i in surrounding_tiles.iter() {
            let index = *s as i32 + i;
            if index >= 0 && index < input.len() as i32 {
                for (j,n) in numbers.iter().enumerate() {
                    if n.contains(&(index as usize)) && !surr_index.contains(&j) {
                        surr_index.push(j);
                    }
                }
            }
        }
    }
    let mut sum = 0;
    for i in surr_index.iter() {
        sum += get_num(&input, &numbers[*i]);
    }
    sum
}
fn parse_input(input: &str) -> Vec<Element> {
    let mut result = Vec::new();
    for c in input.chars() {
        match c {
            '0'..='9' => result.push(Element::Number(c.to_digit(10).unwrap())),
            '.' => result.push(Element::Empty),
            '\r' | '\n' => {}
            _ => result.push(Element::Symbol),
        }
    }
    result
}
fn main() {
    let input = fs::read_to_string("../input.txt")
        .expect("Something went wrong reading the file");
    let start = std::time::Instant::now();
    let width = input.find('\n').unwrap()-1;
    let result = parse_input(&input);
    let sum = calc_surrounding_sum(result,width as i32);
    
    let duration = start.elapsed();
    println!("Finished after {:?}", duration);
    println!("Result: {}", sum);
}
