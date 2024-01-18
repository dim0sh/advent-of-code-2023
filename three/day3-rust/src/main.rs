use std::fs;

enum Element {
    Number(u32),
    Empty,
    Symbol,
}
// fn print_vec(vec: &Vec<Element>) {
//     for e in vec {
//         print_element(e);
//     }
//     println!();
// }
// fn print_element(e: &Element) {
//     match e {
//         Element::Number(n) => print!("{}", n),
//         Element::Empty => print!("."),
//         Element::Symbol => print!("#"),
//     }
// }
fn calc_surrounding_sum(input: Vec<Element>, width:i32) -> u32 {
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
    let sum = input.iter().enumerate().map(|(idx, elem)| {
        match elem {
            Element::Symbol => {
                surrounding_tiles.iter().map(|tile|{
                    let i = idx as i32;
                    let mut sub_sum = 0;
                    if (i+tile) >= 0 && (i+tile) < input.len() as i32 {
                        let index = (i+tile) as usize;
                        match input[index] {
                            Element::Number(n) => {
                                sub_sum += n;
                                // TODO:
                                // check for nums with more than one digit
                                // numbers in same row not twice
                            },
                            _ => {},
                        }
                    }
                    sub_sum
                }).sum::<u32>()
            }
            _ => {0}
        }
    }).sum();

    sum
}
fn parse_input(input: &str) -> u32 {
    let width = input.find('\n').unwrap()-1;
    let mut result = Vec::new();
    for c in input.chars() {
        match c {
            '0'..='9' => result.push(Element::Number(c.to_digit(10).unwrap())),
            '.' => result.push(Element::Empty),
            '\r' | '\n' => {}
            _ => result.push(Element::Symbol),
        }
    }
    calc_surrounding_sum(result, width as i32)
}

fn main() {
    let input = fs::read_to_string("../input.txt")
        .expect("Something went wrong reading the file");
    let start = std::time::Instant::now();
    let result = parse_input(&input);
    let duration = start.elapsed();
    println!("{:?}",result);
    println!("Finished after {:?}", duration)
}
