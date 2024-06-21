fn main() {
    use std::time::Instant;

    let start = Instant::now();
    for _i in 0..1000000 {}
    let elapsed= (start.elapsed().as_micros() as f64) / 1000000.0;

    println!("{:.8?}sec", elapsed);
}