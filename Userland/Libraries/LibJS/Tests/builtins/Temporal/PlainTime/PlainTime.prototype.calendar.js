describe("correct behavior", () => {
    test("basic functionality", () => {
        const plainTime = new Temporal.PlainTime();
        expect(plainTime.calendar).toBeInstanceOf(Temporal.Calendar);
        expect(plainTime.calendar.id).toBe("iso8601");
    });
});

test("errors", () => {
    test("this value must be a Temporal.PlainTime object", () => {
        expect(() => {
            Reflect.get(Temporal.PlainTime.prototype, "calendar", "foo");
        }).toThrowWithMessage(TypeError, "Not a Temporal.PlainTime");
    });
});
