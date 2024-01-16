use std::{fs, vec};
struct Game {
    id: u32,
    red: Vec<u32>,
    blue: Vec<u32>,
    green: Vec<u32>,
    length: usize,
}
fn parse_draw(game: &mut Game, draw: &str, set: usize) {
    let mut i: usize = 0;
    while (draw.as_bytes()[i] != b'g') && (draw.as_bytes()[i] != b'b') && (draw.as_bytes()[i] != b'r') {
        i += 1;
    }
    let color = draw[0..i].parse::<u32>().unwrap();
    match draw.as_bytes()[i] {
        b'g' => game.green[set] = color,
        b'b' => game.blue[set] = color,
        b'r' => game.red[set] = color,
        _ => {},
    }
}
fn parse_input(input: &str) -> Game{
    let mut game = Game {
        id: 0,
        red: vec![0; 10],
        blue: vec![0; 10],
        green: vec![0; 10],
        length: 0,
    };
    let mut i: usize = 4;
    while input.as_bytes()[i] != b':' {
        i += 1;
    }
    game.id = input[5..i].parse::<u32>().unwrap();
    
    let _res = input[i+1..].chars().filter(|c| !c.is_whitespace())
        .collect::<String>()
        .split(';')
        .enumerate()
        .for_each(|(idx,set)| {
            set.split(',')
            .for_each(|draw| {
                parse_draw(&mut game, draw, idx);
            });
            game.length = idx+1;
        });
    return game;
}
fn valid_game(game: &Game) -> u32 {
    let mut valid = 0;
    for i in 0..game.length {
        if game.red[i] <= 12 && game.blue[i] <= 14 && game.green[i] <= 13 {
            valid += 1;
        }
    }
    return game.id * (valid/game.length as u32);
}
fn min_num_colors(game: &Game) -> u32 {
    let mut red_min = 0;
    let mut blue_min = 0;
    let mut green_min = 0;
    for i in 0..game.length {
        if game.red[i] > red_min {
            red_min = game.red[i];
        }
        if game.blue[i] > blue_min {
            blue_min = game.blue[i];
        }
        if game.green[i] > green_min {
            green_min = game.green[i];
        }
    }
    return red_min * blue_min * green_min;
}
fn main() {
    let mut sum = 0;
    let input = fs::read_to_string("../input.txt")
        .expect("Something went wrong reading the file");
    let start = std::time::Instant::now();
    for line in input.lines() {
        let game = parse_input(line);
        sum += valid_game(&game);
        // sum += min_num_colors(&game);
    }
    let duration = start.elapsed();
    println!("{} duration: {:?}", sum, duration);
}
